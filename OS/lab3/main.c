#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <locale.h>

#define NSTEP_N 100

enum OP_TYPE {
    O_WRITE,
    O_READ,
    O_TOTAL
};

typedef struct Parameters {
    int tracks;
    int heads;
    int sectors;
    int rpm;
    double tm;
    double tmax;
    double ts;
    double tr;
    double tw;
} Parameters;

struct Parameters* pars;

typedef struct Request {
    double time;
    int track;
    int head;
    int sector;
    enum OP_TYPE op;
} Request;

typedef struct Queue {
    struct Request** reqs;
    int len;
    int size;
} Queue;

typedef struct Data {
    int totalProcessed;
    double* processTime;
    int maxQueue;
    double idleTime;
    size_t overflow_count;
} Data;

struct Request* generateReq(double t) {
    struct Request* req = (Request*)malloc(sizeof(struct Request));
    req->time = t + rand() % (int)pars->tmax;
    req->track = rand() % pars->tracks;
    req->head = rand() % pars->heads;
    req->sector = (rand() % pars->sectors) + 1;
    req->op = rand() % O_TOTAL;
    return req;
}

struct Queue* generateQueue() {
    struct Queue* queue = (Queue*)malloc(sizeof(struct Queue));
    queue->len = 0;
    queue->size = 4096;
    queue->reqs = (Request**)malloc(queue->size * sizeof(struct Request*));
    struct Request* req = generateReq(0);
    while (req->time < pars->tm) {
        if (queue->len == queue->size) {
            queue->size *= 2;
            queue->reqs = (Request**)realloc(queue->reqs, queue->size * sizeof(struct Requests*));
        }
        queue->reqs[queue->len++] = req;
        req = generateReq(req->time);
    }
    return queue;
}

int getLastOnTime(struct Queue* queue, int i, double t) {
    while (i+1 < queue->len && queue->reqs[i+1]->time <= t) {
        i++;
    }
    return i;
}

int timeToSector(int sector, double t) {
    int totalSects = t / pars->tr;
    int currSector = totalSects % pars->sectors;
    int diff = sector - currSector;
    double offset = t - totalSects * pars->tr;
    return diff >= 0 ? diff * pars->tr - offset : (diff + pars->sectors) * pars->tr - offset;
}

double processReq(struct Request* req, int currTrack, double t) {
    int track = req->track;
    double tp = abs(track - currTrack) * pars->ts;
    double to = timeToSector(req->sector, t + tp);
    double trw = req->op ? pars->tw : pars->tr;
    return tp + to + trw;
}

double Min(double *values, size_t len) {
    double min = INFINITY;
    for (int i = 0; i < len; i++) {
        if (values[i] < min) {
            min = fmin(values[i], min);
        }
    }
    return min;
}

double Max(double *values, int len) {
    double max = -INFINITY;
    for (int i = 0; i < len; i++) {
        if (values[i] > max) {
            max = fmax(values[i], max);
        }
    }
    return max;
}

double Avg(double* values, int len) {
    double sum = 0;
    for (int i = 0; i < len; i++) {
        sum += values[i];
    }
    return sum / len;
}

double AC(double* values, int len, double avg) {
    double ac = 0;
    for (int i = 0; i < len; i++) {
        ac += pow(values[i] - avg, 2);
    }
    return sqrt(ac/len);
}

struct Parameters* initParameters(int tracks, int heads, int sectors, int rpm, int tm, int tmax, double ts) {
    struct Parameters* p = (Parameters*)malloc(sizeof(struct Parameters));
    p->tracks = tracks;
    p->heads = heads;
    p->sectors = sectors;
    p->rpm = rpm;
    p->tm = tm;
    p->tmax = tmax;
    p->ts = ts;
    p->tr = 60000.0 / ((double)rpm * sectors);
    p->tw = p->tr + p->tr * sectors;
    return p;
}

void printParameters(struct Parameters* p) {
    printf("Входные данные:\n");
    printf("Кол-во дорожек: %d\n", p->tracks);
    printf("Кол-во головок: %d\n", p->heads);
    printf("Кол-во секторов: %d\n", p->sectors);
    printf("Скорость вращения: %d\n", p->rpm);
    printf("Время моделирования: %f\n", p->tm);
    printf("Время перехода головки на соседнюю дорожку: %f\n", p->ts);
    printf("Время чтения: %f\n", p->tr);
    printf("Время записи: %f\n", p->tw);
    printf("_________________________________\n");
}

void printResult(struct Queue* que, struct Data* data) {
    double minPT = Min(data->processTime, data->totalProcessed);
    double maxPT = Max(data->processTime, data->totalProcessed);
    double avgPT = Avg(data->processTime, data->totalProcessed);
    double acPT = AC(data->processTime, data->totalProcessed, avgPT);
    printf("Обработано запросов: %d из %d\n", data->totalProcessed, que->len);
    printf("Минимальное время обслуживания: %f (мс)\n", minPT);
    printf("Максимальное время обслуживания: %f (мс)\n", maxPT);
    printf("Среднее время обслуживания: %f (мс)\n", avgPT);
    printf("Среднеквадратическое отклонение от среднего времени обслуживания: %f (мс)\n", acPT);
    printf("Максимальная длина очереди запросов: %i\n", data->maxQueue);
    printf("Время простоя дисковой подсистемы: %f (мс)\n", data->idleTime);
    printf("Кол-во переполнения очереди запросов: %zu\n", data->overflow_count);
    int bin1 = 0;
    int bin10 = 0;
    int bin100 = 0;
    int bin1000 = 0;
    int binInf = 0;
    for (int i = 0; i < data->totalProcessed; i++) {
        double v = data->processTime[i];
        if (v < 1) bin1++;
        else if (v < 10) bin10++;
        else if (v < 100) bin100++;
        else if (v < 1000) bin1000++;
        else binInf++;
    }

    printf("-------------------------------------\n");
    printf("< 1 мс: %i\n", bin1);
    printf(">= 1 мс и < 10 мс: %i\n", bin10);
    printf(">= 10 мс и < 100 мс: %i\n", bin100);
    printf(">= 100 мс и < 1000 мс: %i\n", bin1000);
    printf("> 1000 мс: %i\n", binInf);
}

struct Data* FIFO(struct Queue* q) {
    int track = 0;
    int bufStart = 0;
    int bufEnd = -1;
    double time = 0;
    struct Data* data = (Data*)malloc(sizeof(struct Data));
    data->totalProcessed = 0;
    data->processTime = (double*)malloc(q->len*sizeof(double));
    data->maxQueue = 0;
    data->idleTime = 0;
    data->overflow_count = 0;
    
    while (bufStart < q->len) {
        bufEnd = getLastOnTime(q, bufEnd, time);
        int que = bufEnd - bufStart;
        if (que > data->maxQueue)
            data->maxQueue = que;
        if (que < 0) {
            struct Request* next = q->reqs[bufStart];
            data->idleTime += next->time - time;
            time = next->time;
            continue;
        }
        struct Request* req = q->reqs[bufStart];
        double treq = processReq(req, track, time);
        time += treq;
        if (time >= pars->tm) {
            bufEnd = getLastOnTime(q, bufEnd, time);
            int queue = bufEnd - bufStart;
            if (queue > data->idleTime) data->maxQueue = queue;
            return data;
        }
        track = req->track;
        data->processTime[data->totalProcessed++] = time - req->time;
        bufStart++;
    }
    return data;
}

int compareRequests(const void* a, const void* b) {
    struct Request* r1 = *(struct Request**)a;
    struct Request* r2 = *(struct Request**)b;

    if (r1->track < r2->track) return -1;
    if (r1->track > r2->track) return 1;
    return 0;
}

int compareRequestsRev(const void* a, const void* b) {
    struct Request* r1 = *(struct Request**)a;
    struct Request* r2 = *(struct Request**)b;

    if (r1->track < r2->track) return 1;
    if (r1->track > r2->track) return -1;
    return 0;
}

struct Data* FSCAN(struct Queue* q) {
    int track = 0;
    int bufStart = 0;
    int bufEnd = -1;
    int dir = 1;
    double time = 0;
    Data* data = (Data*)malloc(sizeof(Data));
    data->totalProcessed = 0;
    data->processTime = (double*)malloc(q->len * sizeof(double));
    data->maxQueue = 0;
    data->idleTime = 0;
    data->overflow_count = 0;

    while (bufStart < q->len) {
        bufEnd = getLastOnTime(q, bufEnd, time);
        int que = bufEnd - bufStart;
        if (que > data->maxQueue)
            data->maxQueue = que;
        if (que < 0) {
            struct Request* next = q->reqs[bufStart];
            data->idleTime += next->time - time;
            time = next->time;
            continue;
        }

        int len = bufEnd - bufStart + 1;
        if (len >= NSTEP_N) {
            data->overflow_count++;
            bufEnd -= len - NSTEP_N;
            len = NSTEP_N;
        }

        Request* reqs[NSTEP_N];
        memcpy(reqs, q->reqs + bufStart, sizeof(reqs));
        qsort(reqs, len, sizeof(struct Request*), dir ? compareRequests:compareRequestsRev);
        for (int i = 0; i < len; i++) {
            struct Request* req = reqs[i];
            double treq = processReq(req, track, time);
            time += treq;
            if (time >= pars->tm) {
                bufEnd = getLastOnTime(q, bufEnd, time);
                int queue = bufEnd - bufStart;
                if (queue > data->maxQueue) {
                    data->maxQueue = queue;
                }
                return data;
            }
            track = req->track;
            data->processTime[data->totalProcessed++] = time - req->time;
        }
        bufStart += len;
        dir = !dir;
    }
    return data;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    pars = initParameters(500, 4, 1, 10000, 5 * 50 * 1000, 20, 2);
    printParameters(pars);
    srand(time(0));
    struct Queue* q = generateQueue();
    struct Data* FIFOData = FIFO(q);
    struct Data* FSCANData = FSCAN(q);
    printf("Tmax = %f, Стратегия: FIFO\n", pars->tmax);
    printResult(q, FIFOData);
    printf("________________________________\n");
    printf("Tmax = %f, Стратегия: FSCAN\n", pars->tmax);
    printResult(q, FSCANData);
    printf("________________________________\n");
    return 0;
}
