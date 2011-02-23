#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void TextFromLst(QStringList & lst, QTextEdit * ed, QString otst, int & l_index)
{

    QVector<ushort> vt;
    int cur_l_index = l_index;

    foreach(QString tec_str, lst)
    {
        ushort tekSymb = tec_str.utf16()[0];
        if(!vt.contains(tekSymb))
        {
            vt.append(tekSymb);
        };
    };

    qSort(vt);

    ed->append(otst + QString("curPnt%2->pontcnt = %1;").arg(vt.count()).arg(cur_l_index));
    //ed->append(otst + QString("curPnt%1->Result = -1;").arg(l_index));
    ed->append(otst + QString("curPnt%2->symbols = new wchar_t[%1];").arg(vt.count()).arg(cur_l_index));
    ed->append(otst + QString("curPnt%2->childrens = new NodePoint[%1];").arg(vt.count()).arg(cur_l_index));

    int ind = 0;


    foreach(ushort tekSymb, vt)
    {
        ed->append(otst + QString("curPnt%4->symbols[%1] = %2; //%3").arg(ind).arg(tekSymb).arg(QChar(tekSymb)).arg(cur_l_index));

        QStringList pLst;
        int cur_Rezult = -1;

        foreach(QString tec_str, lst)
        {
            ushort tekSymb2 = tec_str.utf16()[0];
            if (tekSymb2 == tekSymb)
            {
                if (tec_str.length() == 1)
                {
                    cur_Rezult = 9999;
                    continue;
                };
                QString tt_str = tec_str.mid(1);
                pLst.append(tt_str);
            };
        };

        int pListCnt = pLst.count();

        switch(pListCnt)
        {
            case(0):
            {
                ed->append(otst + QString("   curPnt%1->childrens[%2].Result = %3;").arg(cur_l_index).arg(ind).arg(cur_Rezult));
                ed->append(otst + QString("   curPnt%1->childrens[%2].pontcnt = 0;").arg(cur_l_index).arg(ind));
                ed->append(otst + QString("   curPnt%1->childrens[%2].childrens = 0;").arg(cur_l_index).arg(ind));
                ed->append(otst + QString("   curPnt%1->childrens[%2].symbols = 0;").arg(cur_l_index).arg(ind));
                break;
            };
            case(1):
            {
                ed->append(otst + QString("   curPnt%1->childrens[%2].Result = %3;").arg(cur_l_index).arg(ind).arg(9999));
                ed->append(otst + QString("   curPnt%1->childrens[%2].pontcnt = 0;").arg(cur_l_index).arg(ind));
                ed->append(otst + QString("   curPnt%1->childrens[%2].childrens = 0;").arg(cur_l_index).arg(ind));

                QString ostatokStr = pLst.at(0);
                int lenghtOst = ostatokStr.length();
                const ushort* p_str_loc1 = ostatokStr.utf16();
                ed->append(otst + QString("   curPnt%1->childrens[%2].symbols = new wchar_t[%3]; //%4").arg(cur_l_index).arg(ind).arg(lenghtOst+1).arg(ostatokStr));
                int iii = 0;
                do{
                    ed->append(otst + QString("   curPnt%1->childrens[%2].symbols[%3] = %4; //%5").arg(cur_l_index).arg(ind).arg(iii).arg(p_str_loc1[iii]).arg(ostatokStr.at(iii)));
                    iii++;
                }while((--lenghtOst) > 0);
                ed->append(otst + QString("   curPnt%1->childrens[%2].symbols[%3] = 0;").arg(cur_l_index).arg(ind).arg(iii));
                break;
            };
            default:
            {
                l_index++;
                ed->append(otst + QString("curPnt%1->childrens[%2].Result = %3;").arg(cur_l_index).arg(ind).arg(cur_Rezult));
                ed->append(otst + QString("   NodePoint* curPnt%1 = &curPnt%2->childrens[%3];").arg(l_index).arg(cur_l_index).arg(ind));

                TextFromLst(pLst, ed, otst+"   ",l_index);

                break;
            };
        };


        ind++;
    };




};

void Dialog::on_pushButton_clicked()
{
    ui->textEdit->clear();

    int cnt = ui->listWidget->count();
    if (cnt==0)
        return;

    QStringList lst;
    for(int i=0; i<cnt;i++)
    {
        lst.append(ui->listWidget->item(i)->text());
    };

    QTextEdit * ed = ui->textEdit;

    ed->append("");
    ed->append("//Объявление");
    ed->append("struct NodePoint");
    ed->append("{");
    ed->append("    uint pontcnt;");
    ed->append("    int Result;");
    ed->append("    NodePoint* childrens;");
    ed->append("    wchar_t* symbols;");
    ed->append("};");
    ed->append("");
    ed->append("");

    ed->append("//Инициализация");
    ed->append("NodePoint* t_methods_Rus_tree = new NodePoint;");
    ed->append("");
    ed->append("");
    ed->append("NodePoint* curPnt0 = t_methods_Rus_tree;");
    ed->append("curPnt0->Result = -1;");
    ed->append("");

    int mainind = 0;
    TextFromLst(lst, ed, QString(""), mainind);

    ed->append("");


}

void Dialog::on_AddpushButton_2_clicked()
{
    ui->listWidget->addItem(QString("ОткрытьФайл"));
    ui->listWidget->addItem(QString("Закрыть"));
    ui->listWidget->addItem(QString("Прочитать"));
    ui->listWidget->addItem(QString("ЗначениеАтрибута"));
    ui->listWidget->addItem(QString("ИмяАтрибута"));
    ui->listWidget->addItem(QString("КоличествоАтрибутов"));
    ui->listWidget->addItem(QString("ПолучитьАтрибут"));
    ui->listWidget->addItem(QString("ПрочитатьАтрибут"));
    ui->listWidget->addItem(QString("ТипАтрибута"));

}

void Dialog::on_DelpushButton_2_clicked()
{

}
