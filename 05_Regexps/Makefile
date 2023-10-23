test:	esub
	@rm -f output*
	@echo "123abcde123" | ./esub "\([a-b]\+\)c\(d\)e*" "---\0--\1--\2--\0---" > output1
	@echo "123abcde123" | sed -E 's/([a-b]+)c(d)e*/---\0--\1--\2--\0---/' > output2
	@echo "123456" | ./esub "\(1\(2\(3\(4\)\)\)\)" "\1\2\4\3" >> output1
	@echo "123456" | sed -E 's/(1(2(3(4))))/\1\2\4\3/' >> output2
	@echo "abcddcba" | ./esub "\(.\)..\1" "\0\0" >> output1
	@echo "abcddcba" | sed -E 's/(.)..\1/\0\0/' >> output2
	@if cmp output1 output2; then \
		echo "Same"; \
	else \
		echo "!!!ERROR!!! Not same"; \
	fi
	
esub:
	@cc esub.c -O0 -g -o esub
clear:
	rm -vf esub output*
