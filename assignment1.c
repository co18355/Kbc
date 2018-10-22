#include<stdio.h>
#include<string.h>
void print_all_packages(town t) {
    printf("%s:\n",t.name);
    for(int i=0; i<t.offices_count; i++)
    {
        printf("\t%d:\n",i);
        for(int j=0; j<t.offices[i].packages_count; j++)
            printf("\t\t%s\n",t.offices[i].packages[j].id);
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
    int max = target->offices[target_office_index].max_weight;
    int min = target->offices[target_office_index].min_weight;
    package* temp = NULL;
    int notaccept = 0, weight;
    post_office* s = source->offices + source_office_index;
    post_office* d = target->offices + target_office_index;
                         
    for(int i=0; i < s->packages_count; i++)
    {
        weight = s->packages[i].weight;
        if(weight <= max && weight >= min)
        {
            d->packages_count++;
            d->packages = (package*)realloc(d->packages, sizeof(package) * d->packages_count);
            d->packages[d->packages_count-1] = s->packages[i];         
        }
        else
        {
            notaccept++;
            temp = (package*)realloc(temp, sizeof(package) * notaccept);
            temp[notaccept-1] = s->packages[i];
        }
    }
    s->packages = temp;
    s->packages_count = notaccept;
}
 
 town town_with_most_packages(town* towns, int towns_count) {
    town max_town;
    int sum, max = 0;
    for(int i=0; i<towns_count; i++)
    {
        sum = 0;
        for(int j=0; j<towns[i].offices_count; j++)
            sum += towns[i].offices[j].packages_count;
        if(max < sum)
        {
            max_town = towns[i];
            max = sum;
        }
    }
    return max_town;
}

town* find_town(town* towns, int towns_count, char* name) {
    for(int i=0; i<towns_count; i++)
    {
        if(strcmp(towns[i].name,name) == 0)
            return towns + i; 
    }
    return NULL;
}
