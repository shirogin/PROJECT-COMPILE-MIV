cd ./syntax
bison -d ./syntax.y
cd ../lexical
flex ./lexical.l
cd ..
gcc ./lexical/lex.yy.c ./syntax/syntax.tab.c -lfl -ly -o app.out
rm ./lexical/lex.yy.c
rm ./syntax/syntax.tab.c
./app.out ./program.miv