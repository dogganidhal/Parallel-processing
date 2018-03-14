fun main(args:Array<String>){

    var array = Array(1000000){0} //Initialise un tableau de 1M de cellules à 0

    for (i in 0..(array.count() - 1))
    {
        array.set(i, i * i)
        println(array[i])
    }
}