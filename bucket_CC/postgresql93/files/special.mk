.if ${OPSYS:MFreeBSD}
TEMPLATE_ARG=	--with-template=freebsd
UUID_ARG=	--with-uuid=bsd
.elif ${OPSYS:MDragonFly}
TEMPLATE_ARG=	--with-template=freebsd
UUID_ARG=	--with-uuid=bsd
.elif ${OPSYS:MNetBSD}
TEMPLATE_ARG=	--with-template=netbsd
UUID_ARG=	--with-uuid=bsd
.elif ${OPSYS:MOpenBSD}
TEMPLATE_ARG=	--with-template=openbsd
UUID_ARG=	--with-uuid=bsd
.elif ${OPSYS:MDarwin}
TEMPLATE_ARG=	--with-template=darwin
UUID_ARG=	--with-uuid=e2fs
.elif ${OPSYS:MSunOS}
TEMPLATE_ARG=	--with-template=solaris
# UUID?
.elif ${OPSYS:MLinux}
TEMPLATE_ARG=	--with-template=linux
UUID_ARG=	--with-uuid=e2fs
.endif

