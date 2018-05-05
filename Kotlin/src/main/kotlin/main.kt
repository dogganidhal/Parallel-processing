import kotlin.system.exitProcess

fun compute_for_index(index: Int) : Int
{
    var res = 0
    for (i in 0..index)
    {
        res += i
    }
    return res
}

fun main(args: Array<String>)
{
    if (args.size !=2)
    {
        println("Please specify two arguments: [-s | -p] [Array Size]")
        exitProcess(0)
    }
    else if(args[0] == "-s")
    {
        //Sequential Way
        sequential(args[1].toInt())
    }
    else if(args[0] == "-p")
    {
        //Parallel Way
        multithreading(args[1].toInt())
    }
    else
    {
        println("Error while catching the args")
        exitProcess(0)
    }

}