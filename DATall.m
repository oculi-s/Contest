function ALL = DATall(NEW, PATH)
    ALL.Y17 = 0;
    ALL.Y18 = 0;
    for i = 1:length(NEW.TIME)/2
        ALL.Y17 = ALL.Y17 + sum(NEW.TIME{i}(:,5:end),1);
        ALL.Y18 = ALL.Y18 + sum(NEW.TIME{i+12}(:,5:end),1);
    end
    ALL.Y17 = ALL.Y17 / sum(ALL.Y17);
    ALL.Y18 = ALL.Y18 / sum(ALL.Y18);
    ALL.Y17 = ALL.Y17(end-8:end);
    ALL.Y18 = ALL.Y18(end-8:end);
    
    fig = plot(15:23,ALL.Y17,'--','color','r');
    hold on; plot(15:23,ALL.Y18,'b'); hold off;
        
    temp = ylim;
    ALL.MID17 = (15:23)*ALL.Y17'/sum(ALL.Y17);
    ALL.MID18 = (15:23)*ALL.Y18'/sum(ALL.Y18);    
    hold on; plot(ones(1,100).*ALL.MID17,linspace(temp(1),temp(2)),'--','color','r'); hold off;
    hold on; plot(ones(1,100).*ALL.MID18,linspace(temp(1),temp(2)),'b'); hold off;

    tempname = '2017년과 2018년의 전체 유동인구 비교';
    title(tempname);
    ylabel('percentage(%)');
    legend(string(2017),string(2018));

    cd(PATH.tot);
    saveas(fig, string(tempname)+'.png');
end