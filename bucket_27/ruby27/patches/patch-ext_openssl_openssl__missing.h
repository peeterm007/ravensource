--- ext/openssl/openssl_missing.h.orig	2020-03-31 10:44:55 UTC
+++ ext/openssl/openssl_missing.h
@@ -72,6 +72,9 @@ void ossl_HMAC_CTX_free(HMAC_CTX *);
 #if !defined(HAVE_X509_STORE_SET_EX_DATA)
 #  define X509_STORE_set_ex_data(x, idx, data) \
 	CRYPTO_set_ex_data(&(x)->ex_data, (idx), (data))
+#endif
+
+#if !defined(HAVE_X509_STORE_GET_EX_NEW_INDEX)
 #  define X509_STORE_get_ex_new_index(l, p, newf, dupf, freef) \
 	CRYPTO_get_ex_new_index(CRYPTO_EX_INDEX_X509_STORE, (l), (p), \
 				(newf), (dupf), (freef))
@@ -145,6 +148,7 @@ void ossl_X509_REQ_get0_signature(const
 #endif
 
 #if !defined(HAVE_OPAQUE_OPENSSL)
+#if defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x2070000fL
 #define IMPL_PKEY_GETTER(_type, _name) \
 static inline _type *EVP_PKEY_get0_##_type(EVP_PKEY *pkey) { \
 	return pkey->pkey._name; }
@@ -196,6 +200,7 @@ IMPL_PKEY_GETTER(EC_KEY, ec)
 #undef IMPL_PKEY_GETTER
 #undef IMPL_KEY_ACCESSOR2
 #undef IMPL_KEY_ACCESSOR3
+#endif
 #endif /* HAVE_OPAQUE_OPENSSL */
 
 #if !defined(EVP_CTRL_AEAD_GET_TAG)
