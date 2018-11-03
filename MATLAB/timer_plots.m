close all;
pthreads = csvread('pthreads_data.csv');
omp = csvread('omp_data.csv');
cilk = csvread('cilk_data.csv');
for i = 1:13
    for j = 1:8
        for k = 1:2
            matrix(i,j,k) = mean(pthreads(8*(i-1)+1:8*(i-1)+8,k + 2)) / pthreads(8*(i-1)+j,5); 
        end
    end
end

figure('Name','Mesh on pthreads qsort-stdlib','NumberTitle','off');
[x,y]=meshgrid(log2(pthreads(1:8:97,1)),log2(pthreads(1:8,2)));
surf(x,y,matrix(:,:,1)');
hold on;
surf(x,y,ones(13,8)');
xlabel('Array Size (2^q)', 'FontSize', 18);
ylabel('Number of Threads (2^p)', 'FontSize', 18);
zlabel('Excecuton Time Ratio (seq/par)', 'FontSize', 18);
colorbar;

figure('Name','Mesh on pthreads qsort_seq','NumberTitle','off');
surf(x,y,matrix(:,:,2)');
hold on;
surf(x,y,ones(13,8)');
xlabel('Array Size (2^q)', 'FontSize', 18);
ylabel('Number of Threads (2^p)', 'FontSize', 18);
zlabel('Excecuton Time Ratio (seq/par)', 'FontSize', 18);
colorbar;

for i = 1:13
    for j = 1:8
        for k = 1:2
            matrix(i,j,k) = mean(omp(8*(i-1)+1:8*(i-1)+8,k + 2)) / omp(8*(i-1)+j,5); 
        end
    end
end

figure('Name','Mesh on omp qsort-stdlib','NumberTitle','off');
[x,y]=meshgrid(log2(omp(1:8:97,1)),log2(omp(1:8,2)));
surf(x,y,matrix(:,:,1)');
hold on;
surf(x,y,ones(13,8)');
xlabel('Array Size (2^q)', 'FontSize', 18);
ylabel('Number of Threads (2^p)', 'FontSize', 18);
zlabel('Excecuton Time Ratio (seq/par)', 'FontSize', 18);
colorbar;

figure('Name','Mesh on omp qsort_seq','NumberTitle','off');
surf(x,y,matrix(:,:,2)');
hold on;
surf(x,y,ones(13,8)');
xlabel('Array Size (2^q)', 'FontSize', 18);
ylabel('Number of Threads (2^p)', 'FontSize', 18);
zlabel('Excecuton Time Ratio (seq/par)', 'FontSize', 18);
colorbar;

for i = 1:13
    for j = 1:8
        for k = 1:2
            matrix(i,j,k) = mean(cilk(8*(i-1)+1:8*(i-1)+8,k + 2)) / cilk(8*(i-1)+j,5); 
        end
    end
end

figure('Name','Mesh on cilk qsort-stdlib','NumberTitle','off');
[x,y]=meshgrid(log2(cilk(1:8:97,1)),log2(cilk(1:8,2)));
surf(x,y,matrix(:,:,1)');
hold on;
surf(x,y,ones(13,8)');
xlabel('Array Size (2^q)', 'FontSize', 18);
ylabel('Number of Threads (2^p)', 'FontSize', 18);
zlabel('Excecuton Time Ratio (seq/par)', 'FontSize', 18);
colorbar;

figure('Name','Mesh on cilk qsort_seq','NumberTitle','off');
surf(x,y,matrix(:,:,2)');
hold on;
surf(x,y,ones(13,8)');
xlabel('Array Size (2^q)', 'FontSize', 18);
ylabel('Number of Threads (2^p)', 'FontSize', 18);
zlabel('Excecuton Time Ratio (seq/par)', 'FontSize', 18);
colorbar;