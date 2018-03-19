

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <omp.h>
#include <string.h>
#include <unistd.h>

using namespace std;

#define BITS 12                   /* Setting the number of bits to 12, 13*/
#define HASHING_SHIFT BITS - 8    /* or 14 affects several constants.    */
#define MAX_VALUE (1 << BITS) - 1 /* Note that MS-DOS machines need to   */
#define MAX_CODE MAX_VALUE - 1    /* compile their code in large model if*/
                                  /* 14 bits are selected.               */
#if BITS == 14
#define TABLE_SIZE 18041 /* The string table size needs to be a */
#endif                   /* prime number that is somewhat larger*/
#if BITS == 13           /* than 2**BITS.                       */
#define TABLE_SIZE 9029
#endif
#if BITS <= 12
#define TABLE_SIZE 5021
#endif

/* MF modified */
int *code_value;                  /* This is the code value array        */
unsigned int *prefix_code;        /* This array holds the prefix codes   */
unsigned char *append_character;  /* This array holds the appended chars */
unsigned char decode_stack[4000]; /* This array holds the decoded string */

void compress(ifstream &, ofstream &);
int find_match(int, unsigned int);
void expand(istream &, ostream &);
unsigned char *decode_string(unsigned char *, unsigned int);
int input_code(istream &);
void output_code(ostream &, unsigned int);

void compress(ifstream &input, ofstream &output)
{
    unsigned int next_code;
    unsigned int character;
    unsigned int string_code;
    unsigned int index;
    int i;
    ofstream output_code_file;

    output_code_file.open("outputcodes", ios::out);

    next_code = 256;
    for (i = 0; i < TABLE_SIZE; i++)
        code_value[i] = -1;

    i = 0;
    string_code = input.get();
    while ((character = input.get()) != (unsigned)EOF)
    {
        index = find_match(string_code, character);
        if (code_value[index] != -1)
            string_code = code_value[index];
        else
        {
            if (next_code <= MAX_CODE)
            {
                code_value[index] = next_code++;
                prefix_code[index] = string_code;
                append_character[index] = character;
            }

            output_code_file << string_code << "\n";

            output_code(output, string_code);
            string_code = character;
        }
    }
    output_code(output, string_code);
    output_code_file << string_code << "\n";
    output_code(output, MAX_VALUE);
    output_code(output, 0);
    output_code_file.close();
    unlink("outputcodes");
}

/*
** This is the hashing routine.  It tries to find a match for the prefix+char
** string in the string table.  If it finds it, the index is returned.  If
** the string is not found, the first available index in the string table is
** returned instead.
*/

int find_match(int hash_prefix, unsigned int hash_character)
{
    int index;
    int offset;

    index = (hash_character << (HASHING_SHIFT)) ^ hash_prefix;
    if (index == 0)
        offset = 1;
    else
        offset = TABLE_SIZE - index;
    while (1)
    {
        if (code_value[index] == -1)
            return (index);
        if (prefix_code[index] == hash_prefix &&
            append_character[index] == hash_character)
            return (index);
        index -= offset;
        if (index < 0)
            index += TABLE_SIZE;
    }
}

/*
**  This is the expansion routine.  It takes an LZW format file, and expands
**  it to an output file.  The code here should be a fairly close match to
**  the algorithm in the accompanying article.
*/

void expand(istream &input, ostream &output)
{
    unsigned int next_code;
    unsigned int new_code;
    unsigned int old_code;
    int character;
    unsigned char *string;
    ofstream input_code_file;

    next_code = 256;

    old_code = input_code(input);
    character = old_code;
    
    output.put((char)old_code);

    input_code_file.open("inputcodes", ios::out);

    input_code_file << old_code << "\n";
    while ((new_code = input_code(input)) != (MAX_VALUE))
    {
        input_code_file << new_code << "\n";
        if (new_code >= next_code)
        {
            *decode_stack = character;
            string = decode_string(decode_stack + 1, old_code);
        }
        else
            string = decode_string(decode_stack, new_code);
        character = *string;
        while (string >= decode_stack)
            output.put(*string--);
        if (next_code <= MAX_CODE)
        {
            prefix_code[next_code] = old_code;
            append_character[next_code] = character;
            next_code++;
        }
        old_code = new_code;
    }
}

/*
** This routine simply decodes a string from the string table, storing
** it in a buffer.  The buffer can then be output in reverse order by
** the expansion program.
*/

unsigned char *decode_string(unsigned char *buffer, unsigned int code)
{
    int i;

    i = 0;
    while (code > 255)
    {
        *buffer++ = append_character[code];
        code = prefix_code[code];
        if (i++ >= 4094)
        {
            cout << "Fatal error during code expansion.\n";
            exit(0);
        }
    }
    *buffer = code;
    return (buffer);
}

/*
** The following two routines are used to output variable length
** codes.  They are written strictly for clarity, and are not
** particularyl efficient.
*/

int input_code(istream &input)
{
    unsigned int return_value;
    static int input_bit_count = 0;
    static unsigned long input_bit_buffer = 0L;

    while (input_bit_count <= 24)
    {
        input_bit_buffer |=
            (unsigned long)input.get() << (24 - input_bit_count);
        input_bit_count += 8;
    }
    return_value = input_bit_buffer >> (32 - BITS);
    input_bit_buffer <<= BITS;
    input_bit_count -= BITS;
    return (return_value);
}

void output_code(ostream &output, unsigned int code)
{
    static int output_bit_count = 0;
    static unsigned long output_bit_buffer = 0L;

    output_bit_buffer |= (unsigned long)code << (32 - BITS - output_bit_count);
    output_bit_count += BITS;
    while (output_bit_count >= 8)
    {
        output.put((char)(output_bit_buffer >> 24));
        output_bit_buffer <<= 8;
        output_bit_count -= 8;
    }
}

void parse_args(int argc, char *argv[], vector<char *> &files, bool &pflag)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0)
            pflag = true;
        else
            files.push_back(argv[i]);
    }
}

void compress_input(vector<char *> files, bool pflag)
{
    int i;
    for (i = 0; i < files.size(); i++)
    {
        ifstream file(files.at(i));
        ofstream output(string(files.at(i)) + ".xc");
        compress(file, output);
        file.close();
    }
}

int main(int argc, char *argv[])
{

    bool pflag = false;
    vector<char *> files;

    parse_args(argc, argv, files, pflag);

    auto begin = chrono::high_resolution_clock::now();

    code_value = new int[TABLE_SIZE * sizeof(unsigned int)];
    prefix_code = new unsigned int[TABLE_SIZE * sizeof(unsigned int)];
    append_character = new unsigned char[TABLE_SIZE * sizeof(unsigned char)];

    if (code_value == NULL || prefix_code == NULL || append_character == NULL)
    {
        cout << "Fatal error allocating table space!\n";
        exit(EXIT_FAILURE);
    }

    compress_input(files, pflag);

    auto end = chrono::high_resolution_clock::now();

    cout << files.size() << " files compressed " << "in: " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;

    return EXIT_SUCCESS;
}