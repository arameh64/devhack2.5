
Խնդիր 1. Բառը լոգերում (սկրիպտը՝ Slack-ից)
Նախապատրաստում.
1) Slack-ից ներբեռնել logs_generator.sh ֆայլը և տեղադրել աշխատանքային թղթապանակում։
2) Տալ գործարկման իրավունք և գործարկել սկրիպտը.
   chmod +x logs_generator.sh
   ./logs_generator.sh
3) Սկրիպտը կստեղծի լոգ ֆայլեր տարբեր թղթապանակներում և կտպի ձեր տարբերակը՝ ֆայլը և բառը։ Տարբերակը կախված է ՕՀ-ից (macOS/Linux) և պատահական է յուրաքանչյուրի համար։ Տեքստը պահպանված է նաև task_card.txt ֆայլում։
Լոգ ֆայլի տողերն ունեն հետևյալ տեսքը՝
2026-10-25 08:25:42 [ERROR] backup: Packet lost
Առաջադրանք.
Ստեղծել log_search.h և log_search.c ֆայլերը հետևյալ ֆունկցիաներով.
• char *map_log(const char *path, int *size) — open()-ով բացում է ֆայլը, lseek()-ով որոշում է չափը, mmap()-ով (PROT_READ, MAP_PRIVATE) արտապատկերում է և վերադարձնում ցուցիչը,
• void unmap_log(char *data, int size),
• int count_word(const char *data, int size, const char *word) — հաշվում է, թե քանի անգամ է word-ը հանդիպում տվյալների մեջ։
main.c-ում ֆայլի անունը և բառը ստանալ argv-ով և տպել արդյունքը։
Հուշում՝ mmap-ով ստացված տվյալները '\0'-ով չեն ավարտվում, ուստի strstr()-ը այստեղ չի աշխատի։ Ամեն դիրքում համեմատել strncmp()-ով։
Կապակցել (link) օբյեկտային ֆայլերի միջոցով.
   gcc -c log_search.c
   gcc -c main.c
   gcc main.o log_search.o -o log_search
Ստուգում՝
   ./log_search <ֆայլ> <բառ>
   ./logs_generator.sh check <ստացված թիվը>
Օրինակ՝
«ERROR» բառը հանդիպում է 95 անգամ


Խնդիր 2. Թաքնված թվանշաններ
Ստեղծել digits.h և digits.c ֆայլերը int digit_sum_file(const char *path, int *count) ֆունկցիայով։ Ֆունկցիան mmap()-ով (PROT_READ, MAP_PRIVATE) արտապատկերում է ֆայլը, անցնում է բոլոր սիմվոլներով և գումարում է միայն թվանշանները ('0'–'9')։ Թվանշանների քանակը վերադարձնել count-ի միջոցով, իսկ գումարը՝ որպես արդյունք։
main.c-ում ֆայլի անունը ստանալ argv-ով։
Կապակցել մեկ հրամանով.
   gcc main.c digits.c -o digits
shop.txt՝
Hello, my order number is 4521.
Bread 350, Milk 600, Apple 250
Ելք՝
Թվանշանների քանակը՝ 13
Թվանշանների գումարը՝ 33


Խնդիր 3. Ամենաերկար տողը
Ստեղծել lines.h և lines.c ֆայլերը.
• char *map_text(const char *path, int *size) և void unmap_text(char *data, int size),
• int find_longest_line(const char *data, int size, int *start, int *len) — գտնում է ամենաերկար տողը, start-ում և len-ում պահում է դրա սկիզբը և երկարությունը, իսկ վերադարձնում է տողի համարը։
main.c-ում տպել տողի համարը, երկարությունը և հենց տողը (fwrite(data + start, 1, len, stdout))։
Կապակցել օբյեկտային ֆայլերի միջոցով։
poem.txt՝
C is simple
mmap maps a file into memory
pipes connect processes
Ելք՝
Ամենաերկար տողը՝ 2-րդը (28 սիմվոլ)
mmap maps a file into memory


Խնդիր 4. XOR ծածկագիր հենց ֆայլի մեջ (MAP_SHARED)
Ստեղծել xor_file.h և xor_file.c ֆայլերը int xor_file(const char *path, char key) ֆունկցիայով։ Ֆունկցիան բացում է ֆայլը O_RDWR ռեժիմով, արտապատկերում է PROT_READ | PROT_WRITE և MAP_SHARED դրոշակներով, յուրաքանչյուր բայթի վրա կիրառում է XOR key-ով, կանչում է msync() և munmap()։ Վերադարձնում է մշակված բայթերի քանակը։
main.c-ում ֆայլի անունը և բանալի-սիմվոլը ստանալ argv-ով։
Կապակցել մեկ հրամանով։
Ստուգում՝
   echo "Meet me at 7 near the library" > note.txt
   ./xor_file note.txt K
   cat note.txt          → անհասկանալի տեքստ
   ./xor_file note.txt K
   cat note.txt          → Meet me at 7 near the library
Հարց՝ ինչու՞ է նույն ծրագիրը և՛ գաղտնագրում, և՛ վերծանում ֆայլը։


Խնդիր 5. Վիճակախաղ (ընդհանուր հիշողություն)
Ստեղծել lottery.h և lottery.c ֆայլերը.
• int *create_numbers(int n) — mmap()-ով (MAP_SHARED | MAP_ANONYMOUS) ստեղծում է n int-ից բաղկացած ընդհանուր զանգված,
• void free_numbers(int *numbers, int n),
• void draw_numbers(int *numbers, int n, int max) — զանգվածը լրացնում է 1-ից max միջակայքի n հատ իրարից տարբեր պատահական թվերով,
• int count_matches(const int *a, const int *b, int n) — հաշվում է, քանի թիվ կա երկու զանգվածներում էլ։
main.c-ում.
• օգտվողը մուտքագրում է իր տոմսի 6 թվերը (1–49),
• ծնողը ստեղծում է 6 int-ի ընդհանուր զանգված և կատարում fork(),
• երեխան կանչում է srand(getpid()) և draw_numbers(), ապա ավարտվում է,
• ծնողը սպասում է երեխային (wait()), տպում է խաղարկված թվերը և համընկնումների քանակը։
Կապակցել ստատիկ գրադարանով՝ liblottery.a (ar rcs հրամանով), կոմպիլացնելիս օգտագործել -L. -llottery դրոշակները.
   gcc -c lottery.c
