#include <stdio.h>
#include <string.h>

static char bufferDump[1024];

void dmp_buf(const char *text, const unsigned char *buf, unsigned int len)
{
    char txt[17];
    unsigned int i, idx = 0;
    snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "[DUMP] %s 0x%08X (%u bytes)\n", text, (int)buf, len);
    printf(bufferDump);
    idx = 0;
    memset(txt, 0, sizeof(txt));
    for (i = 0; i < len; i++)
    {
        if (i >= 4096)
            break;
        if (i % 16 == 0)
        {
            if (i > 0)
            {
                snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "  %s\n", txt);
                printf(bufferDump);
                idx = 0;
                memset(txt, 0, sizeof(txt));
            }
            idx += snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "%04X: ", (unsigned int)i);
        }
        idx += snprintf(bufferDump + idx, sizeof(bufferDump) - idx, " %02X", (unsigned int)buf[i]);
        txt[i % 16] = (buf[i] > 31 && buf[i] < 127) ? buf[i] : '.';
    }
    if (len > 0)
    {
        for (/* i = i */; i % 16 != 0; i++)
            idx += snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "   ");
        snprintf(bufferDump + idx, sizeof(bufferDump) - idx, "  %s\n", txt);
        printf(bufferDump);
    }
}