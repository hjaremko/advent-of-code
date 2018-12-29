package pl.jaremko.advent

import java.io.File

fun main(args: Array<String>) {
    val inputFile = File("input.txt")
    var inputArr = ArrayList<String>()

    var two = 0
    var three = 0

    inputFile.forEachLine{ inputArr.add( it ) }

    for ( str in inputArr ) {
        var letters = IntArray( 26 )

        for ( letter in str ) {
            letters[ letter.toInt() - 'a'.toInt() ]++
        }

        if ( letters.contains( 2 ) ) {
            two++
        }

        if ( letters.contains( 3 ) ) {
            three++
        }
    }

    println( two * three )

    for ( i in 0..inputArr.size - 1 ) {
        for ( j in i + 1..inputArr.size - 1 ) {
            var common = inputArr[ i ]
            var first = 0
            var second = 0

            while ( first < inputArr[ i ].length ) {
                if ( inputArr[ i ][ first ] != inputArr[ j ][ second ] ) {
                    common = common.removeRange( 0, 1 );
                }

                first++
                second++
            }

            if ( common.length == inputArr[ i ].length - 1 ) {
                println( common )
            }
        }
    }
}
