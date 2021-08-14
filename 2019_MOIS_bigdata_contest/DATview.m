function SUM = DATview(MAT,NEW,PATH)
    SUM = struct();
    AREA = [11010 11110 11130 31021 31022 31023];
    AREAname = ["서울종로구" "서울노원구" "서울서대문구" "성남수정구" "성남중원구" "성남분당구"];    
    
    if(isdir("DATA_SUM"))
        rmdir DATA_SUM s;
    end
    mkdir DATA_SUM;
        
    if(isdir("DATA_VIEW"))
        rmdir DATA_VIEW s;
    end
    mkdir DATA_VIEW;
    
    for i = 1:length(AREA)
        SUM.TIME{i} = zeros(length(NEW.TIME)+1,13);
        for j = 1:length(NEW.TIME)
            temp = cell2mat(NEW.TIME(j));
            tempdata(j,1:4) = temp(i+1,1:4);
            tempdata(j,5:13) = temp(i+1,end-8:end);
        end
        tempdata(:,end-8:end) = 100*tempdata(:,end-8:end)./sum(tempdata(:,end-8:end));
        SUM.TIME{i}(1,:) = ["Date" "Area" "X" "Y" 15:23];
        SUM.TIME{i}(2:end,:) = tempdata;
        tempname = "FLOW_SUM_BY_AREA_"+AREA(i)+".csv";
        cd(PATH.sum);
        dlmwrite(tempname,SUM.TIME(i),'precision',9);
        
        ts = timeseries(SUM.TIME{i}(2:end,i+4));
        ts.TimeInfo.Units = 'months';
        ts.TimeInfo.StartDate = '00-Jan-2017';
        ts.TimeInfo.Format = 'mm, yyyy';
        
        set(gcf,'Visible', 'off');
        fig = plot(ts);
        tempname = string(SUM.TIME{i}(1,i+4))+'시 월별 '+string(AREAname(i)+' 유동인구');
        title(tempname);
        ylabel('percentage(%)');
        
        cd(PATH.view);
        saveas(fig, tempname+'.png');
    end
    close all;
    
    for i = 1:length(AREA)
        for j = 1:length(NEW.TIME)/2
            temp1 = NEW.TIME{j}(i+1,:);
            temp2 = NEW.TIME{j+12}(i+1,:);
            tempdata = [NEW.TIME{j}(1,:);temp1;temp2];
            tempdata(2:3,5:end) = tempdata(2:3,5:end)./sum(tempdata(2:3,5:end),2);
            
            set(gcf,'Visible', 'off');
            fig = plot(tempdata(1,end-8:end),tempdata(2,end-8:end),'--','color','r');
            hold on; plot(tempdata(1,end-8:end),tempdata(3,end-8:end),'b'); hold off;
            SUM.MID{j}(1,:) = tempdata(1,end-8:end)*tempdata(2,end-8:end)'/sum(tempdata(2,end-8:end));
            SUM.MID{j}(2,:) = tempdata(1,end-8:end)*tempdata(3,end-8:end)'/sum(tempdata(3,end-8:end));
            hold on; plot(ones(1,100).*SUM.MID{j}(1,1),linspace(0.01, 0.08),'--','color','r'); hold off;
            hold on; plot(ones(1,100).*SUM.MID{j}(2,1),linspace(0.01, 0.08),'b'); hold off;
            
            tempname = string(tempdata(2,1))+'과 '+string(tempdata(3,1))+'의 '+string(AREAname(i)+' 유동인구');
            title(tempname);
            ylabel('percentage(%)');
            ylim([0.01 0.08]);
            legend(string(tempdata(2,1)),string(tempdata(3,1)));
            
            cd(PATH.view);
            saveas(fig, tempname+'.png');
        end
    end
    close all;
end