--- pattern.c.orig	2020-05-02 21:08:56 UTC
+++ pattern.c
@@ -57,6 +57,7 @@ static const struct pattern_flags
 }
 Flags[] =
 {
+  { 'a', MUTT_THREADCOMPLETE,	0,		NULL },
   { 'A', MUTT_ALL,			0,		NULL },
   { 'b', MUTT_BODY,  MUTT_FULL_MSG|MUTT_SEND_MODE_SEARCH, eat_regexp },
   { 'B', MUTT_WHOLE_MSG,  MUTT_FULL_MSG|MUTT_SEND_MODE_SEARCH, eat_regexp },
@@ -1493,6 +1494,16 @@ mutt_pattern_exec (struct pattern_t *pat
       else
         result = mutt_is_list_cc (pat->alladdr, h->env->to, h->env->cc);
       return (pat->not ^ result);
+    case MUTT_THREADCOMPLETE:
+      { static pattern_t tmp;
+        static short pattern_set = 0;
+        if(! pattern_set) {
+          memset (&tmp, 0, sizeof (tmp));
+          tmp.op = MUTT_TAG;
+          pattern_set = 1;
+        }
+        return (pat->not ^ (h->env && match_threadcomplete(&tmp, flags, ctx, h->thread, 1, 1, 1, 1)));
+      } 
     case MUTT_SUBSCRIBED_LIST:
       if (cache)
       {
