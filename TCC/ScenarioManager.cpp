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