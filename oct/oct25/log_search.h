//   /home/arameh64/.local/state/practice3/app/app.log (390 տող)
//   /home/arameh64/.local/state/practice3/database/db.log (588 տող)
//   /home/arameh64/.local/state/practice3/network/net.log (538 տող)
//   /home/arameh64/.local/state/practice3/network/archive/net.1.log (544 տող)
//   /tmp/practice3_arameh64/cache/cache.log (550 տող)


#ifndef LOG_SEARCH_H
#define LOG_SEARCH_H

char *map_log(const char *path, int *size);
void unmap_log(char *data, int size);
int count_word(const char *data, int size, const char *word);

#endif