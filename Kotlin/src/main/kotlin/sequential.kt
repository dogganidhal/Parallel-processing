import kotlin.system.measureTimeMillis

fun sequential(array_size: Int){

    var array = Array(array_size){0} //Initialise un tableau de 1M de cellules à 0

    val time = measureTimeMillis({
        for (i in 0..(array.count() - 1))
        {
            array.set(i, compute_for_index(i))
            //println(array[i])
        }
    })

    println("Time: $time ms")

    /*for (i in 0..(array.count() - 1))
    {
        println(array[i])
    }*/
    
}