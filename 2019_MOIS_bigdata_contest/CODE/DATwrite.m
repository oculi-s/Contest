function NEW = DATwrite(MAT, PATH)
    NEW = struct();
    AREA = [11010 11110 11130 31021 31022 31023];
    if(isdir("DATA_NEW"))
        rmdir DATA_NEW s;
    end
    mkdir DATA_NEW;
    
    for i = 1:length(MAT.TIME)
        cd(PATH.new);
        
        temp = cell2mat(MAT.TIME(i));
        temparea = floor(temp(:,2)/1e+15);
        tempname = "FLOW_TIME_SUM_"+string(temp(1,1))+".csv";
        tempdata = zeros(length(AREA),size(temp,2));
        
        tempdata(1,:) = ["Date" "Area" "X" "Y" 0:23];
        for j = 1:length(AREA)
            position = find(~(temparea-AREA(j)));
            tempdata(j+1,:) = sum(temp(position,:));
            tempdata(j+1,1:4) = temp(position(end),1:4);
        end
        NEW.TIME{i} = tempdata;
        dlmwrite(tempname,NEW.TIME(i),'precision',9);
    end
    for i = 1:length(MAT.WKDY)
        cd(PATH.new);
        temp = cell2mat(MAT.WKDY(i));
        temparea = floor(temp(:,2)/1e+15);
        tempname = "FLOW_WKDY_SUM_"+string(temp(1,1))+".csv";
        tempdata = zeros(1+length(AREA),size(temp,2));
        
        tempdata(1,:) = ["Date" "Area" "X" "Y" 1 2 3 4 5];
        for j = 1:length(AREA)
            position = find(~(temparea-AREA(j)));
            tempdata(j+1,5:end) = sum(temp(position,5:end));
            tempdata(j+1,1:4) = temp(position(end),1:4);
        end
        NEW.WKDY{i} = tempdata;
        dlmwrite(tempname,NEW.WKDY(i),'precision',19);
    end
end