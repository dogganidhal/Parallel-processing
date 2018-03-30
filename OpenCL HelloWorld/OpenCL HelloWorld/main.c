//
//  main.c
//  OpenCL HelloWorld
//
//  Created by Nidhal DOGGA on 3/29/18.
//  Copyright © 2018 Nidhal DOGGA. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <OpenCL/Opencl.h>
#include "chrono.h"
#include "io.h"

typedef enum { SEQUENTIAL, PARALLEL } processingMode;

void parseArgs(int argc, char *argv[], size_t *numberOfIterations, processingMode *mode)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./helloWorld [-p|s] numberOfIterations");
        exit(EXIT_FAILURE);
    }
    *mode = strcmp(argv[1], "-p") == 0 ? PARALLEL : SEQUENTIAL;
    *numberOfIterations = atoi(argv[2]);
}

long long sumForIndex(size_t index)
{
    long long sum = 0;
    for (size_t i = 0; i < index; i++)
        sum += i;
    return sum;
}

void computeSequentially(size_t numberOfIterations)
{
    long long values[numberOfIterations];
    
    for (size_t index = 0; index < numberOfIterations; index++)
        values[index] = sumForIndex(index);
    
}

void computeConcurrently(size_t numberOfIterations)
{
    
    int status;                            // error code returned from api calls
    
    size_t global;                      // global domain size for our calculation
    size_t local;                       // local domain size for our calculation
    
    cl_device_id device_id;             // compute device id
    cl_context context;                 // compute context
    cl_command_queue commands;          // compute command queue
    cl_program program;                 // compute program
    cl_kernel kernel;                   // compute kernel
    
    cl_mem values;
    
    // Connect to a compute device
    //
    status = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
    if (status != CL_SUCCESS)
    {
        printf("Error: Failed to create a device group!\n");
        exit(EXIT_FAILURE);
    }
    
    // Create a compute context
    //
    context = clCreateContext(0, 1, &device_id, NULL, NULL, &status);
    if (!context)
    {
        printf("Error: Failed to create a compute context!\n");
        exit(EXIT_FAILURE);
    }
    
    // Create a command commands
    //
    commands = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &status);
    if (!commands)
    {
        printf("Error: Failed to create a command commands!\n");
        exit(EXIT_FAILURE);
    }
    
    // Create the compute program from the source buffer
    //
    char *kernelSource = readFile("helloWorld.cl");
    program = clCreateProgramWithSource(context, 1, (const char **) & kernelSource, NULL, &status);
    if (!program)
    {
        printf("Error: Failed to create compute program!\n");
        exit(EXIT_FAILURE);
    }
    
    // Build the program executable
    //
    status = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (status != CL_SUCCESS)
    {
        size_t len;
        char buffer[2048];
        
        printf("Error: Failed to build program executable!\n");
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s\n", buffer);
        exit(1);
    }
    
    // Create the compute kernel in the program we wish to run
    //
    kernel = clCreateKernel(program, "compute", &status);
    if (!kernel || status != CL_SUCCESS)
    {
        printf("Error: Failed to create compute kernel!\n");
        exit(1);
    }
    
    values = clCreateBuffer(context, CL_MEM_READ_WRITE, numberOfIterations * sizeof(size_t), NULL, NULL);
    if (values == NULL)
    {
        printf("Error: Failed to allocate device memory!\n");
        exit(EXIT_FAILURE);
    }
    
    // Set the arguments to our compute kernel
    //
    status = 0;
    status |= clSetKernelArg(kernel, 0, sizeof(long long), &numberOfIterations);
    status |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &values);
    if (status != CL_SUCCESS)
    {
        printf("Error: Failed to set kernel arguments! %d\n", status);
        exit(EXIT_FAILURE);
    }
    
    // Get the maximum work group size for executing the kernel on the device
    //
    status = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &local, NULL);
    if (status != CL_SUCCESS)
    {
        printf("Error: Failed to retrieve kernel work group info! %d\n", status);
        exit(EXIT_FAILURE);
    }
    
    // Execute the kernel over the entire range of our 1d input data set
    // using the maximum number of work group items for this device
    //
    global = numberOfIterations * sizeof(size_t);
    cl_event event;
    status = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, &global, &local, 0, NULL, &event);
    if (status)
    {
        printf("Error: Failed to execute kernel!\n");
        exit(EXIT_FAILURE);
    }
    
    // Wait for the command commands to get serviced before reading back results
//    clWaitForEvents(1, &event);
    clFinish(commands);
    
    cl_ulong begin;
    cl_ulong end;
    
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &begin, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
    
    // Shutdown and cleanup
    //
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);
    clReleaseEvent(event);
}

int main(int argc, char *argv[])
{
    size_t numberOfIterations;
    processingMode pmode;
    cl_ulong timeElapsed = 0;
    
    parseArgs(argc, argv, &numberOfIterations, &pmode);
    
    if (pmode == SEQUENTIAL)
    {
        timeElapsed = measure_time(MILLISECONDS, ^{
            computeSequentially(numberOfIterations);
        });
    } else if ( pmode == PARALLEL)
    {
        timeElapsed = measure_time(MILLISECONDS, ^{
            computeConcurrently(numberOfIterations);
        });
    }
    
    printf("time elapsed: %llu ms\n", timeElapsed);
    
    return EXIT_SUCCESS;
}

