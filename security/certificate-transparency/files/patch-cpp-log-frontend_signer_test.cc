--- cpp/log/frontend_signer_test.cc.orig	2016-02-02 11:35:23 UTC
+++ cpp/log/frontend_signer_test.cc
@@ -1,5 +1,8 @@
 /* -*- indent-tabs-mode: nil -*- */
 #include <glog/logging.h>
+// Without this, build will fail due to clash between onigposix.h
+// and regex.h; note it's only compiled with "make check".
+#define GTEST_HAS_POSIX_RE 0
 #include <gmock/gmock.h>
 #include <gtest/gtest.h>
 #include <memory>
