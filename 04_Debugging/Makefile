all:	range
	@echo "source script" | gdb ./range 2>&1 | grep "\\$$" > output
	@if cmp output test; then \
		echo "Same"; \
	else \
		echo "!!!ERROR!!! Not same"; \
	fi
	
range:
	@cc range.c -O0 -g -o range
clear:
	rm -vf range output
