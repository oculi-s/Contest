clc;
close all; clear all;

PATH.orig = 'C:\Users\user\Desktop\bigdata\1';
PATH.old = 'C:\Users\user\Desktop\bigdata\1\DATA';
PATH.new = 'C:\Users\user\Desktop\bigdata\1\DATA_NEW';
PATH.sum = 'C:\Users\user\Desktop\bigdata\1\DATA_SUM';
PATH.view = 'C:\Users\user\Desktop\bigdata\1\DATA_VIEW';
PATH.tot = 'C:\Users\user\Desktop\bigdata\1\DATA_TOT';
PATH.map = 'C:\Users\user\Desktop\bigdata\1\MAP_VIEW';
PATH.file = 'C:\Users\user\Desktop\bigdata\1\MAP_FILE';
PATH.maps = 'C:\Users\user\Desktop\bigdata\1\MAP_NEW';

VALC.TIME = [1:4 5:28];
VALC.WKDY = [1:4 5 6 7 8 9];
VALC.AGE = [1:4 6 7 12 13];
VALC.DMP1 = [1 2 3 6 7 8 9 18 19 20 21 28 29 30 31];
VALC.DMP2 = [1:4 7 8 9 10 19 20 21 22 29 30 31 32];

%% 1-1. data read
cd(PATH.orig);
MAT = DATread(VALC, PATH);

%% 1-2. new data write
cd(PATH.orig);
NEW = DATwrite(MAT, PATH);

%% 1-3. normalization & graphitization
cd(PATH.orig);
SUM = DATview(MAT, NEW, PATH);

%% 1-4. data total
cd(PATH.orig);
TOT = DATtot(SUM, PATH);

%% 1-5. data all
cd(PATH.orig);
ALL = DATall(NEW, PATH);

%% 1-6. save variables
cd(PATH.orig);
save('SAVED_VARIABLES');
