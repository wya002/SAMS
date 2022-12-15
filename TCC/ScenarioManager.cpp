#include "ScenarioManager.h"
#include "tinyxml.h"

void  ScenarioManager::save()
{
	double startX1 = airThreatScenario.getInitPosition().x;
	double startY1 = airThreatScenario.getInitPosition().y;
	double endX2 = airThreatScenario.getTargetPosition().x;
	double endY2 = airThreatScenario.getTargetPosition().y;
	double MSSX = missileScenario.getInitPosition().x;
	double MSSY = missileScenario.getInitPosition().y;

	//xml ����
	TiXmlDocument doc;
	TiXmlDeclaration* pDec1 = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(pDec1);

	//��Ʈ ��� �߰�
	TiXmlElement* pRoot = new TiXmlElement("DB");
	doc.LinkEndChild(pRoot);

	int value = 100;

	// ������� �� ������ �߰�
	// �ó����� ������
	TiXmlElement* pElem = new TiXmlElement("Synario");
	pRoot->LinkEndChild(pElem);

	//������� �� �Ӽ� �߰�
	TiXmlElement* pSubElem = new TiXmlElement("SynarioStart");	// ATS �ʱ���ġ
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("Position", "Value");
	pSubElem->SetAttribute("Start", startX1);
	pSubElem->SetAttribute("End", startY1);

	pSubElem = new TiXmlElement("SynarioDestination");			// ATS ������ġ
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("Position", "Value");
	pSubElem->SetAttribute("Start", endX2);
	pSubElem->SetAttribute("End", endY2);

	pSubElem = new TiXmlElement("SynarioMSS");					// MSS �ʱ���ġ
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("Position", "Value");
	pSubElem->SetAttribute("Start", MSSX);
	pSubElem->SetAttribute("End", MSSY);

	doc.SaveFile("C:/Users/User/Desktop/Test.xml");		// ���� ���� ��ġ
}

void ScenarioManager::load(int x1, int tx)
{
	TiXmlDocument ReadDoc;
	ReadDoc.LoadFile("C:/Users/User/Desktop/Test.xml");

	// ��Ʈ ��������
	TiXmlElement* ReadRoot = ReadDoc.FirstChildElement("DB");
	TiXmlElement* sub1 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioStart");
	TiXmlElement* sub2 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioDestination");
	TiXmlElement* sub3 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioMSS");

	// ��带 �ٷ�� ���� �ڵ�
	TiXmlHandle handle1(0);
	TiXmlHandle handle2(0);
	TiXmlHandle handle3(0);
	handle1 = TiXmlHandle(sub1);
	handle2 = TiXmlHandle(sub2);
	handle3 = TiXmlHandle(sub3);

	TiXmlAttribute* pAttrib1;
	TiXmlAttribute* pAttrib2;
	TiXmlAttribute* pAttrib3;
	pAttrib1 = sub1->FirstAttribute();
	pAttrib2 = sub2->FirstAttribute();
	pAttrib3 = sub3->FirstAttribute();

	// �ʱ���ġ �� ���� �Ҵ�
	pAttrib1 = pAttrib1->Next();
	double ATSInitX = pAttrib1->IntValue();
	pAttrib1 = pAttrib1->Next();
	double ATSInitY = pAttrib1->IntValue();

	// ��ǥ��ġ �� ���� �Ҵ�
	pAttrib2 = pAttrib2->Next();
	double ATSEndX = pAttrib2->IntValue();
	pAttrib2 = pAttrib2->Next();
	double ATSEndY = pAttrib2->IntValue();

	// ��ǥ��ġ �� ���� �Ҵ�
	pAttrib3 = pAttrib3->Next();
	double MSSInitX = pAttrib3->IntValue();
	pAttrib3 = pAttrib3->Next();
	double MSSInitY = pAttrib3->IntValue();

	airThreatScenario.setInitPosition({ ATSInitX , ATSInitY });
	airThreatScenario.setTargetPosition({ ATSEndX , ATSEndY });
	missileScenario.setInitPosition({ MSSInitX , MSSInitY });
}
