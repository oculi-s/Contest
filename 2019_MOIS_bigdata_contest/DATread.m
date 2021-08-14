function MAT = DATread(VALC, PATH)
    cd(PATH.old);
    RAW = dir('*.csv');
    MAT = struct('AGE',cell(1),'TIME',cell(1),'WKDY',cell(1),'DMP1',cell(1),'DMP2',cell(1));
    
    for i = 1:length(RAW)
        tempname = RAW(i).name(6);
        temp = table2array(readtable(RAW(i).name));
        if tempname == "A"
            MAT.AGE{end+1} = temp(2:end,VALC.AGE);
        elseif tempname == "T"
            MAT.TIME{end+1} = temp(2:end,VALC.TIME);
        elseif tempname == "W"
            MAT.WKDY{end+1} = temp(2:end,VALC.WKDY);
        elseif tempname == "K"
            MAT.DMP1{end+1} = temp(2:end,VALC.DMP1);
        else
            MAT.DMP2{end+1} = temp(2:end,VALC.DMP2);
        end
    end
end