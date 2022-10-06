#include <C_CkRss.h>

void ChilkatSample(void)
    {
    HCkRss rss;
    BOOL success;
    HCkRss rssChannel;
    int numItems;
    int i;
    HCkRss rssItem;
    int numCategories;
    int j;

    rss = CkRss_Create();

    // Download from the feed URL:
    success = CkRss_DownloadRss(rss,"http://www.nytimes.com/services/xml/rss/nyt/HomePage.xml");
    if (success != TRUE) {
        printf("%s\n",CkRss_lastErrorText(rss));
        CkRss_Dispose(rss);
        return;
    }

    // Get the 1st channel.
    rssChannel = CkRss_GetChannel(rss,0);
    if (CkRss_getLastMethodSuccess(rss) == FALSE) {
        printf("No channel found in RSS feed.\n");
        CkRss_Dispose(rss);
        return;
    }

    // Display the various pieces of information about the channel:
    printf("Title: %s\n",CkRss_getString(rssChannel,"title"));
    printf("Link: %s\n",CkRss_getString(rssChannel,"link"));
    printf("Description: %s\n",CkRss_getString(rssChannel,"description"));

    // For each item in the channel, display the title, link,
    // publish date, and categories assigned to the post.
    numItems = CkRss_getNumItems(rssChannel);

    for (i = 0; i <= numItems - 1; i++) {
        rssItem = CkRss_GetItem(rssChannel,i);

        printf("----\n");
        printf("Title: %s\n",CkRss_getString(rssItem,"title"));
        printf("Link: %s\n",CkRss_getString(rssItem,"link"));
        printf("pubDate: %s\n",CkRss_getString(rssItem,"pubDate"));

        numCategories = CkRss_GetCount(rssItem,"category");

        if (numCategories > 0) {
            for (j = 0; j <= numCategories - 1; j++) {
                printf("    category: %s\n",CkRss_mGetString(rssItem,"category",j));
            }

        }

        CkRss_Dispose(rssItem);
    }

    CkRss_Dispose(rssChannel);


    CkRss_Dispose(rss);

    }
