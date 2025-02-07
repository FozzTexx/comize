LINK=wcl -q
CC=wcc -q
COM_FLAGS=-s -zu -ms
CFLAGS=-bt=dos -0 $(COM_FLAGS)

hello.com: hello.exe
	exe2bin -q $< $@

hello.exe: hello.obj useless.lib
	$(LINK) $(COM_FLAGS) $< clibs.lib

useless.lib: useless.obj print.obj
	wlib -q -n $@ $<

.c.obj: .AUTODEPEND
	$(CC) $(CFLAGS) -fo=$@ $<

clean : .SYMBOLIC
	rm -f *.obj *.map *.err *.lib *.exe *.com
