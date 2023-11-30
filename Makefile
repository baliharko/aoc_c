
DAY=

run:
	@gcc $(DAY).c -o $(DAY)
	@./$(DAY)
	@rm ./$(DAY)
