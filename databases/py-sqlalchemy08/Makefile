# Created by: Dryice Dong Liu <dryice@dryice.name>
# $FreeBSD$

PORTNAME=	sqlalchemy
PORTVERSION=	0.8.7
CATEGORIES=	databases python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
PKGNAMESUFFIX=	08
DISTNAME=	SQLAlchemy-${DISTVERSION}

MAINTAINER=	nivit@FreeBSD.org
COMMENT=	Python SQL toolkit and Object Relational Mapper 0.8.x

LICENSE=	MIT

TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}nose>0:devel/py-nose \
		${PYTHON_PKGNAMEPREFIX}mock>0:devel/py-mock

USES=		python
USE_PYTHON=	distutils autoplist

PY2TO3_CMD=	${LOCALBASE}/bin/2to3-${PYTHON_VER}
PY2TO3_ARGS=	--no-diffs --nobackups --verbose --write
TEST_TARGET=	do-test

CONFLICTS_INSTALL=	${PYTHON_PKGNAMEPREFIX}sqlalchemy{0[679],10}*

OPTIONS_DEFINE=		DOCS EXAMPLES
OPTIONS_MULTI=		BACKEND
OPTIONS_MULTI_BACKEND=	MSSQL MYSQL PGSQL SQLITE SYBASE
OPTIONS_DEFAULT=	SQLITE

MSSQL_DESC=	MS SQL Server backend
SYBASE_DESC=	Sybase backend

MSSQL_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}mssql>0:databases/py-mssql
PGSQL_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}psycopg2>=2.0.8:databases/py-psycopg2
SQLITE_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}sqlite3>0:databases/py-sqlite3
SYBASE_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}sybase>0:databases/py-sybase

PORTDOCS=		*
PORTEXAMPLES=		*

.include <bsd.port.pre.mk>

.if ${PYTHON_REL} < 3000
MYSQL_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}MySQLdb>=1.2.2:databases/py-MySQLdb
#.else
# At the moment databases/py-pymysql does not build with Python3
# See https://github.com/petehunt/PyMySQL#python-3-0-support
#MYSQL_RUN_DEPENDS=	pymysql>=0.5:databases/py-pymysql
.endif

pre-build:
.if ${PYTHON_REL} >= 3000
	@${PY2TO3_CMD} ${PY2TO3_ARGS} ${WRKSRC}/lib
	@${PY2TO3_CMD} ${PY2TO3_ARGS} ${WRKSRC}/doc
	@${PY2TO3_CMD} ${PY2TO3_ARGS} ${WRKSRC}/examples
.endif

# C extensions are not supported with all versions of Python, so ignore
# errors here if there are no .so files to strip.
post-install:
	-@${STRIP_CMD} ${STAGEDIR}${PYTHON_SITELIBDIR}/sqlalchemy/*.so

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	cd ${WRKSRC}/doc/ && ${COPYTREE_SHARE} . ${STAGEDIR}${DOCSDIR}

post-install-EXAMPLES-on:
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	cd ${WRKSRC}/examples/ && ${COPYTREE_SHARE} . ${STAGEDIR}${EXAMPLESDIR}

do-test:
.if ${PYTHON_REL} >= 3000
	${PY2TO3_CMD} ${PY2TO3_ARGS} ${WRKSRC}/test
.endif
	@cd ${WRKSRC} && ${PYTHON_CMD} sqla_nose.py

.include <bsd.port.post.mk>
