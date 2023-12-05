bin_PROGRAMS=guesser
pkgdata_DATA=ru/LC_MESSAGES/guesser.mo \
               eo/LC_MESSAGES/guesser.mo

<<<<<<< HEAD
@DX_RULES@

doxygen-doc/man/man1/namegen.1:	doxygen-doc

man1_MANS = doxygen-doc/man/man1/namegen.1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

http:	doxygen-doc
	python3 -m http.server --directory $</html

=======
>>>>>>> 581791d36270e0aa9104f0aee1c5afd8a83682cf
ru/LC_MESSAGES/guesser.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

eo/LC_MESSAGES/guesser.mo: eo.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po:	messages.pot
	msgmerge -U $@ $<

eo.po:  messages.pot
	msgmerge -U $@ $<

messages.pot:	guesser.pot guesser.c
	xgettext -k_ -c guesser.c -o messages.new.pot
	cp guesser.pot messages.pot
	msgmerge -U messages.pot messages.new.pot
