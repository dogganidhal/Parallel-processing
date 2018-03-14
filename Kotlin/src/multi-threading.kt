var array = Array(1000000){0}

fun compute_for_index(index: Int) : Int 
{
    var res = 0
    for (i in 0..index)
    {
        res += i
    }
    return res
}


fun main(args: Array<String>) {

    val time = measureTimeMillis({
        var t1 = Thread(Runnable
        {
            run {
                for (i in 0..((array.count()/4) - 1))
                {
                    array.set(i, compute_for_index(i))
                }
            }
        })

        var t2 = Thread(Runnable {
            run {
                for (i in (array.count()/4)..(2*array.count()/4) - 1)
                {
                    array.set(i, compute_for_index(i))
                }
            }
        })

        var t3 = Thread(Runnable {
            run {
                for (i in (2*array.count()/4)..(3*(array.count()/4) - 1))
                {
                    array.set(i, compute_for_index(i))
                }
            }
        })

        var t4 = Thread(Runnable {
            run {
                for (i in (3*array.count()/4)..(array.count() - 1))
                {
                    array.set(i, compute_for_index(i))
                }
            }
        })

        t1.run()
        t2.run()
        t3.run()
        t4.run()

        t1.join()
        t2.join()
        t3.join()
        t4.join()

        for (i in 0..(array.count() - 1))
        {
            println(array[i])
        }
    })

    println("Time :" + time)

}