 #include <stdio.h>
 int main() {
    int mem_size, os_size, n, proc_no, proc_size;
    int partition_size, available_mem, internal_frag = 0, allocated = 0;
    printf("Enter memory size: ");
    scanf("%d", &mem_size);
    printf("Enter memory for OS: ");
    scanf("%d", &os_size);
    available_mem = mem_size - os_size;
    printf("Enter number of partitions: ");
    scanf("%d", &n);
    partition_size = available_mem / n;
    printf("\nEach partition size = %d\n", partition_size);
    while (1) {
        printf("\nEnter process and size: ");
        if (scanf("%d %d", &proc_no, &proc_size) != 2) break;
        if (proc_size <= partition_size && allocated < n) {
            printf("process%d allocated\n", proc_no);
            internal_frag += (partition_size - proc_size);
            allocated++;
        } else printf("process%d blocked\n", proc_no);
        if (allocated == n) break;
    }
    printf("\nInternal fragmentation = %d\n", internal_frag);
    return 0;
}
