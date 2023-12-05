bin_PROGRAMS=guesser
pkgdata_DATA=ru/LC_MESSAGES/guesser.mo \
               eo/LC_MESSAGES/guesser.mo

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
