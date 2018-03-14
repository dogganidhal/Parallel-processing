fun compute_for_index(index: Int) : Int 
{
    var res = 0
    for (i in 0..index)
    {
        res += i
    }
    return res
}

fun main(args:Array<String>){

    var array = Array(1000000){0} //Initialise un tableau de 1M de cellules à 0

    val time = measureMillis({
        for (i in 0..(array.count() - 1))
        {
            array.set(i, compute_for_index(i))
            println(array[i])
        }
    })

    println("Time :" + time)
    
}