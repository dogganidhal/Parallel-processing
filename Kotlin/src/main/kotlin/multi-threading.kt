import kotlinx.coroutines.experimental.*
import java.util.concurrent.atomic.AtomicInteger
import kotlin.system.measureTimeMillis

fun main(args: Array<String>)
{
    var array = Array(100000){0} //Initialise un tableau de 1M de cellules à 0

    val time = measureTimeMillis({
            for (i in 0..(array.count() - 1)) {
                launch {
                    array.set(i, compute_for_index(i))
                }
            }
    })

    println("Time: $time ms")

    /*for (i in 0..(array.count() - 1))
    {
        println(array[i])
    }*/
}