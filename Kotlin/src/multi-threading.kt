var array = Array(1000000){0}

fun main(args: Array<String>){

    var t1 = Thread(Runnable
    {
        run {
            for (i in 0..((array.count()/4) - 1))
            {
                array.set(i, i * i)
            }
        }
    })

    var t2 = Thread(Runnable
    {
        run {
            for (i in (array.count()/4)..(2*array.count()/4) - 1)
            {
                array.set(i, i * i)
            }
        }
    })

    var t3 = Thread(Runnable
    {
        run {
            for (i in (2*array.count()/4)..(3*(array.count()/4) - 1))
            {
                array.set(i, i * i)
            }
        }
    })

    var t4 = Thread(Runnable
    {
        run {
            for (i in (3*array.count()/4)..(array.count() - 1))
            {
                array.set(i, i * i)
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

}