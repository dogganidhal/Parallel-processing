fun compute_for_index(index: Int) : Int
{
    var res = 0
    for (i in 0..index)
    {
        res += i
    }
    return res
}