.DEFAULT_GOAL := run

.PHONY: run
run: run-palindrome run-vector ## Run palindrome and vector programs

.PHONY: run-palindrome
run-palindrome: build-palindrome ## Run palindrome program
	python3 test_palindrome.py

.PHONY: build-palindrome
build-palindrome: ## Build palindrome C module
	python3 setup.py build_ext --inplace

.PHONY: run-vector
run-vector: build-vector ## Run vector program
	./vector_embed

.PHONY: build-vector
build-vector: ## Build vector program
	gcc -o vector_embed vector_embed.c -I/usr/include/python3.10 -lpython3.10

.PHONY: help
help: ## Display help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
