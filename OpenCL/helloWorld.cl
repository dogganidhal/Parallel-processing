__kernel void compute(const size_t numberOfIterations, __global size_t *values)
{
    for (size_t index = 0; index < numberOfIterations; index++)
    {
        size_t sum = 0;
        for (size_t i = 0; i < index; i++)
            sum += i;
        values[index] = sum;
    }
}
