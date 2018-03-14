import kotlin.system.measureTimeMillis

fun main(args:Array<String>){

    var array = Array(10000){0} //Initialise un tableau de 1M de cellules à 0

    val time = measureTimeMillis({
        for (i in 0..(array.count() - 1))
        {
            array.set(i, compute_for_index(i))
            //println(array[i])
        }
    })

    //println("Time: " + time)

    for (i in 0..(array.count() - 1))
    {
        println(array[i])
    }
    
}