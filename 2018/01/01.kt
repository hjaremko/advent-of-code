package pl.jaremko.advent

import java.io.File

object One
{
    @JvmStatic
    fun main(args: Array<String>)
    {
        val file = File("input.txt")
        var frequency = 0
        var delta = 0
        var inputArr = ArrayList<Int>()
        var frequencies = HashMap<Int, Int>()

        file.forEachLine{ inputArr.add( it.toInt() ) };

        var i = 0
        while ( true )
        {
            frequency += inputArr[ i % inputArr.size ]

            if ( frequencies.containsKey( frequency ) )
            {
                println( frequency );
                break;
            }
            else
            {
                frequencies.put( frequency, frequency )
            }

            i++
        }
    }
}
