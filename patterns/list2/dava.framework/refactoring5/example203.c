#ifdef E2BIG
if (errno == E2BIG) {
            return -1;
        } else
#endif
#ifdef EINVAL
        if (errno == EINVAL) {
            return -3;
        } else
#endif
        {
            return -3;
        }