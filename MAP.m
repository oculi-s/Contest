%% 2-1. load variables
clc;
close all; clear all;
cd('C:\Users\user\Desktop\bigdata\1');
load('SAVED_VARIABLES.mat');

%% 2-2. map view
cd(PATH.orig);
MAP = MAPview3(MAT, PATH);

%% 2-3. map sum
cd(PATH.orig);
MAPS = MAPsum(NEW, PATH);

%% 2-4. map concatenation
cd(PATH.orig);
MAPC = MAPcon(PATH);