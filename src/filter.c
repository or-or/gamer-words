#include <stdio.h>
#include <string.h>

const unsigned char fAddress[] = "words";
const unsigned char lineLimit = 255;

FILE * fileIn;
FILE * fileOut;

void substituteCharacter( char * word, int index ) {
    // rules
    switch( word[ index ] ) {
        case 'a':
            word[ index ] = '@';
            break;
        case 'e':
            word[ index] = '3';
            break;
        case 'g':
            word[ index ] = '6';
            break;
        case 'i':
            word[ index ] = '1';
            break;
        case 'o':
            word[ index ] = '0';
            break;
        case 'l':
            word[ index ] = '1';
            break;
        case 'c':
            word[ index ] = 'k';
            break;
        case 'k':
            word[ index ] = 'c';
            break;
    }
}

void filter( char word[] ) {

    int limit = strlen( word )-1;
    int index = 0;
    int set[ limit ];
    char copy[ limit ];
    
    // construct set
    for( int i = 0; i < limit; i += 1 ) {
        switch( word[i] ) {
            case 'a':
            case 'c':
            case 'e':
            case 'g':
            case 'i':
            case 'o':
            case 'k':
            case 'l':
                set[index] = i;
                index += 1;
                break;
        }
    }

    // construct power set
    // GfG implementation no author credited
    for( int i = 0; i < ( 1 << index ); i += 1 ) {
        strcpy( copy, word );
        for( int j = 0; j < index; j += 1 ) {
            if( i & ( 1 << j ) ) {
                substituteCharacter( copy, set[ j ] );
            }
        }
        fputs( copy, fileOut );
    }
}


int main() {
    char line[ lineLimit ];

    fileIn = fopen( fAddress, "r" );
    fileOut = fopen( "words_out", "w" );

    if( fileIn == NULL ) {
        printf( "No valid input file." );
        fclose( fileIn );
        return 0;
    }

    while( fgets( line, lineLimit, fileIn ) ) {
        filter( line );
    };

    fclose( fileIn );
    fclose( fileOut );

    return 0;
}
