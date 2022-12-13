#include "ScenarioManager.h"
#include "tinyxml.h"

void ScenarioManager::load()
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
	int x1 = pAttrib1->IntValue();
	pAttrib1 = pAttrib1->Next();
	int y1 = pAttrib1->IntValue();

	// ��ǥ��ġ �� ���� �Ҵ�
	pAttrib2 = pAttrib2->Next();
	int x2 = pAttrib2->IntValue();
	pAttrib2 = pAttrib2->Next();
	int y2 = pAttrib2->IntValue();

	// ��ǥ��ġ �� ���� �Ҵ�
	pAttrib3 = pAttrib3->Next();
	int x3 = pAttrib3->IntValue();
	pAttrib3 = pAttrib3->Next();
	int y3 = pAttrib3->IntValue();

}
