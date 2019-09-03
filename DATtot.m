function TOT = DATtot(SUM, PATH)
    if(isdir("DATA_TOT"))
        rmdir DATA_TOT s;
    end
    mkdir DATA_TOT;
    
    tempsize = size(cell2mat(SUM.TIME(1)));
    TOT.TIME = zeros(tempsize(1),tempsize(2)-3);
    TOT.TIME(:,1) = SUM.TIME{1}(:,1);
    for i = 1:length(SUM.TIME)
        TOT.TIME(:,2:end) = TOT.TIME(:,2:end) + SUM.TIME{i}(:,5:end); 
    end
    TOT.TIME(1,:) = TOT.TIME(1,:)/length(SUM.TIME);
    
    for i = 1:size(SUM.TIME{1}(1,:),2)-1
        set(gcf,'Visible', 'off');
        fig = plot(TOT.TIME(1,2:end),TOT.TIME(i+1,2:end),'--','color','r');
        hold on; plot(TOT.TIME(1,2:end),TOT.TIME(i+13,2:end),'b'); hold off;
        
        TOT.MID(2*i-1,:) = TOT.TIME(1,2:end)*TOT.TIME(i+1,2:end)'/sum(TOT.TIME(i+1,2:end));
        TOT.MID(2*i,:) = TOT.TIME(1,2:end)*TOT.TIME(i+13,2:end)'/sum(TOT.TIME(i+13,2:end));
        temp = ylim;
        hold on; plot(ones(1,100).*TOT.MID(2*i-1,:),linspace(temp(1),temp(2)),'--','color','r'); hold off;
        hold on; plot(ones(1,100).*TOT.MID(2*i,:),linspace(temp(1),temp(2)),'b'); hold off;
            
        tempname = string(TOT.TIME(i+1,1))+'과 '+string(TOT.TIME(i+13,1))+'의 전체 유동인구';
        title(tempname);
        ylabel('percentage(%)');
        legend(string(TOT.TIME(i+1,1)),string(TOT.TIME(i+13,1)));

        cd(PATH.tot);
        saveas(fig, tempname+'.png');
    end
    
    close all;
end