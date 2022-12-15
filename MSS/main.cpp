#include "UDPSocket.h"
#include "Launcher.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <ctime>

using namespace std;

vector<string> split(string str, char Delimiter);
string split_messageName(string receivedMessage);
Position split_message_Pos(string receivedMessage);

int main()
{
    // �޽��� ������ �� ��� Position���� �ٲ��� ���ΰ�? �� �߰�
    // �޽��� ������ �� ��� ���¸� �ٲ��� ���ΰ�?

    Launcher launcher;
    Missile& missile = launcher.getMissileinfo();

    TCC tcc = TCC("127.0.0.1", 9000);
	UDPSocket udp = UDPSocket(tcc, missile);

	thread t([&]() { udp.sendData(); });
	thread t2([&]() { udp.receiveData(); });
    t.join();
    t2.join();


    ATS ats;

    Position mssInitPos;
    Position receivedatsPos;
    Position result;

    string receivedMessage1 = "MI:3.14,5.43";
    string receivedMessage2 = "AP:5.14,4.43";

    string messageName1 = split_messageName(receivedMessage1);
    Position receivedData1 = split_message_Pos(receivedMessage1);

    string messageName2 = split_messageName(receivedMessage2);
    Position receivedData2 = split_message_Pos(receivedMessage2);

    mssInitPos = receivedData1;
    receivedatsPos = receivedData2;

    //cout << "Received ats pos: " << receivedatsPos.x << ", " << receivedatsPos.y << endl;
    //cout << "Received mss pos: " << mssInitPos.x << ", " << mssInitPos.y << endl;


    

    // TCC�� ���� �޾ƿ��� ���°�
    int i = 4;

    while (i != 6)
    {
        cin >> i;

        TCCstate tccstate;

        if (i == 1)
            tccstate = TCCstate::STBY;
        else if (i == 2)
            tccstate = TCCstate::OPERATION;
        else if (i == 3)
            tccstate = TCCstate::PAUSE;
        else if (i == 4)
            tccstate = TCCstate::END;

        switch (tccstate)
        {
        case TCCstate::STBY:
            cout << "STBY" << endl;
            // ats, launcher, missile �ʱ� ��ġ ����
            ats.setACurPos(receivedatsPos);
            launcher.setLinitPos(mssInitPos);
            missile.setinitMcurPos(mssInitPos);
            // launcher ����, missile ���� stop���� ����
            launcher.setLstateSTOP();
            missile.setMstateSTOP();

            cout << "Setting ats pos: " << ats.getACurPos().x << ", " << ats.getACurPos().y << endl;
            cout << "Setting mss pos: " << missile.getMcurPos().x << ", " << missile.getMcurPos().y << endl;

            break;

        case TCCstate::OPERATION:
            cout << "OPERATION" << endl;
            cout << "Received ats pos: " << ats.getACurPos().x << ", " << ats.getACurPos().y << endl;
            cout << "Received mss pos: " << missile.getMcurPos().x << ", " << missile.getMcurPos().y << endl;

            // launcher �߻� ����
            ats.setACurPos(receivedatsPos);

            launcher.launch();

            missile.setMstateCHASE();

            // missile : setAcurPos -> setMcurPos -> getMcurPos
            missile.setAcurPos(ats.getACurPos());

            // Missile::setinitMcurPos(Position initMcurPos)
            missile.setinitMcurPos(launcher.getLinitPos());

            missile.setMcurPos();
            result = missile.getMcurPos();

            if (missile.checkEvent() == true)
            {
                cout << "Intercepted" << endl;
                // TCC���� ����̺�Ʈ �߻� �޽��� �����ֱ� ************
                // TCC���� ����̺�Ʈ �߻� �޽��� �����ֱ� ************
                // TCC���� ����̺�Ʈ �߻� �޽��� �����ֱ� ************
                // �ð� ���� ��Ƽ� �����ֱ�????

                tccstate = TCCstate::END;
            }

            cout << "Send missile pos: " << result.x << ", " << result.y << endl;

            break;

        case TCCstate::PAUSE:
            cout << "PAUSE" << endl;
            result = missile.getMcurPos();

            cout << "Send missile pos: " << result.x << ", " << result.y << endl;

            break;

        case TCCstate::END:
            cout << "END" << endl;

            // TCC���� MSS�� �� ���� �� ���Ѵٰ� ������??
            // TCC�� STBY �϶�� �˷��ֱ�?

            ats.setACurPos(receivedatsPos);
            launcher.setLinitPos(mssInitPos);
            missile.setinitMcurPos(mssInitPos);
            launcher.setLstateSTOP();
            break;
        }
    }

    // std::cout << (ceil(abc * 100) / 100) << std::endl;

    // ���� ��� Position�� ��� �޽����� �ٲ��� ���ΰ�? �� �߰�

    return 0;
}
vector<string> split(string str, char Delimiter) {
    istringstream iss(str);             // istringstream�� str�� ��´�.
    string buffer;                      // �����ڸ� �������� ����� ���ڿ��� ������� ����

    vector<string> result;

    // istringstream�� istream�� ��ӹ����Ƿ� getline�� ����� �� �ִ�.
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);               // ����� ���ڿ��� vector�� ����
    }

    return result;
}
string split_messageName(string receivedMessage)
{
    vector<string> result = split(receivedMessage, ':');

    return result[0];
}
Position split_message_Pos(string receivedMessage)
{
    vector<string> result = split(receivedMessage, ':');
    string message_Pos = result[1];

    vector<string> result2 = split(message_Pos, ',');

    Position received_Pos = { stod(result2[0]), stod(result2[1]) };
    return received_Pos;
}





