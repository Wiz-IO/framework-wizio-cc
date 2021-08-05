
#include <interface.h>

typedef struct STimer_t
{
    struct STimer_t *next;
    uint32_t timeout;
    uint32_t interval;
    bool mode;
    void (*handler)(void);
} STimer_t;

extern STimer_t *TIMER_LIST;

class SoftTimer
{
public:
    SoftTimer() { memset(&THIS_TIMER, 0, sizeof(STimer_t)); }
    ~SoftTimer() { end(); }

    // start timer
    void begin(void (*CB)(void), uint32_t interval /* msec */, bool mode = true /* REPEAT else ONE_SHOT */)
    {
        if (CB && interval)
        {
            THIS_TIMER.mode = mode;
            THIS_TIMER.interval = interval;
            THIS_TIMER.handler = CB;
            if (false == started())
                addSoftTimer(&THIS_TIMER);
        }
    }

    // stop timer
    void end()
    {
        STimer_t *prev = NULL;
        for (STimer_t *t = TIMER_LIST; t; t = t->next)
        {
            if (t == &THIS_TIMER)
            {
                if (prev)
                    prev->next = t->next;
                else
                    TIMER_LIST = t->next;
                if (t->next)
                    t->next->timeout += THIS_TIMER.timeout;
                break;
            }
            prev = t;
        }
    }

    operator bool() { return started(); }

private:
    STimer_t THIS_TIMER;

    bool started()
    {
        for (STimer_t *t = TIMER_LIST; t; t = t->next)
            if (t == &THIS_TIMER)
                return true;
        return false;
    }

    static void addSoftTimer(STimer_t *timer)
    {
        if (TIMER_LIST)
        {
            STimer_t *prev = NULL;
            uint32_t timeout = timer->interval;
            for (STimer_t *t = TIMER_LIST; t; t = t->next)
            {
                if (timeout < t->timeout)
                {
                    t->timeout -= timeout;
                    break;
                }
                else
                    timeout -= t->timeout;
                prev = t;
            }
            timer->timeout = timeout;
            if (prev)
            {
                timer->next = prev->next;
                prev->next = timer;
            }
            else
            {
                timer->next = TIMER_LIST;
                TIMER_LIST = timer;
            }
        }
        else
        {
            timer->next = NULL;
            timer->timeout = timer->interval;
            TIMER_LIST = timer;
        }
    }

public:
    static void loop(void)
    {
        static uint32_t last = 0;
        uint32_t elapsed = millis() - last;
        if (0 == elapsed)
            return;
        last = millis();
        while (TIMER_LIST && (TIMER_LIST->timeout <= elapsed))
        {
            STimer_t *timer = TIMER_LIST;
            elapsed -= TIMER_LIST->timeout;
            TIMER_LIST = TIMER_LIST->next;
            if (true == timer->mode)
                SoftTimer::addSoftTimer(timer);
            if (timer->handler)
                timer->handler();
        }
        if (TIMER_LIST)
            TIMER_LIST->timeout -= elapsed;
    }
};
