TARGETS			+=	gtest/lib/.libs/libgtest.a
TARGETS			+=	libevent/.libs/libevent.a

LOCAL			=	$(PROJECT_ROOT)/3rdparty/.local
MKDIRS			+=	$(LOCAL)

include ../common.mk

gtest/lib/.libs/libgtest.a:	| $(INC) $(LIB) gtest
	cd gtest && ./configure --with-pthreads=no && make && cd .. && \
		$(CP) -rf gtest/lib/.libs/* $(LIB)/ && \
		$(CP) -rf gtest/include/gtest $(INC)/

gtest:
	wget --no-check-certificate http://googletest.googlecode.com/files/gtest-1.6.0.zip -O gtest.zip
	unzip gtest.zip
	rm -rf gtest.zip
	mv gtest-1.6.0 gtest

libevent/.libs/libevent.a:	| $(INC) $(LIB) $(LOCAL) libevent
	cd libevent && ./configure --prefix=$(LOCAL) && make && make install && \
		$(CP) -rf $(LOCAL)/include/* $(INC)/
		$(CP) -rf $(LOCAL)/lib/* $(LIB)/

libevent:
	wget --no-check-certificate https://github.com/downloads/libevent/libevent/libevent-2.0.14-stable.tar.gz -O libevent.tar.gz
	tar zxvf libevent.tar.gz
	rm -rf libevent.tar.gz
	mv libevent-2.0.14-stable libevent

.PHONY: clean
clean::
	cd gtest; make clean
	cd libevent; make clean
	rm -rf .local

cleanall:
	rm -rf gtest
	rm -rf libevent
	rm -rf .local
