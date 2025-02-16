all:	main.o arvore_B.o funcionalidade_1.o funcionalidade_2.o funcionalidade_3.o funcionalidade_4.o funcionalidade_5.o funcionalidade_6.o funcionalidade_7.o funcionalidade_8.o funcionalidade_10.o general.o binarioNaTela.o
	gcc main.o arvore_B.o funcionalidade_1.o funcionalidade_2.o funcionalidade_3.o funcionalidade_4.o funcionalidade_5.o funcionalidade_6.o funcionalidade_7.o funcionalidade_8.o funcionalidade_10.o general.o binarioNaTela.o -o programaTrab

main.o:	main.c
	gcc main.c -c

funcionalidade_1.o: funcionalidade_1.c
	gcc funcionalidade_1.c -c

funcionalidade_2.o: funcionalidade_2.c
	gcc funcionalidade_2.c -c

funcionalidade_3.o: funcionalidade_3.c
	gcc funcionalidade_3.c -c

funcionalidade_4.o: funcionalidade_4.c
	gcc funcionalidade_4.c -c

funcionalidade_5.o: funcionalidade_5.c
	gcc funcionalidade_5.c -c

funcionalidade_6.o: funcionalidade_6.c
	gcc funcionalidade_6.c -c

funcionalidade_7.o: funcionalidade_7.c
	gcc funcionalidade_7.c -c

funcionalidade_8.o: funcionalidade_8.c
	gcc funcionalidade_8.c -c

funcionalidade_10.o: funcionalidade_10.c
	gcc funcionalidade_10.c -c

arvore_B: arvore_B.c
	gcc arvore_B -c

general.o: general.c
	gcc general.c -c

binarioNaTela.o: binarioNaTela.c
	gcc binarioNaTela.c -c

run:
	./programaTrab
clean:
	rm -rf programaTrab *.o
