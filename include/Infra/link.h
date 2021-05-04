#ifndef __LINK_H__
#define __LINK_H__

namespace Infra
{

struct Node;
/**
 * @brief ����ڵ������
*/
struct LinkManager
{
	LinkManager();
	virtual ~LinkManager();
	struct Node* getNode();
	struct Node* begin;
	struct Node* end;
	unsigned int iNode;
};

/**
 * @brief ˫��������
*/
class CLink
{
public:
	CLink();
	virtual ~CLink();
	/**
	* @brief ���������һ������
	* @param payload ����ָ��
	* @param pos �����λ��
	* @param return �ɹ���Ŀǰ�ڵ�ĸ�����ʧ�ܣ�-1
	**/
	int insert(void* payload, unsigned int pos);
	/**
	* @brief ���������Ƴ�һ������
	* @param payload ����ָ��
	* @param pos �Ƴ���λ��
	* @param return Ŀǰ�ڵ�ĸ���
	**/
	int remove(void** payload, unsigned int pos);
	/**
	* @brief ������ĩβ����һ������
	* @param payload ����ָ��
	* @param return Ŀǰ�ڵ�ĸ���
	**/
	int rise(void* payload);
	/**
	* @brief ������ĩβɾ��һ������
	* @param payload ����ָ��
	* @param return Ŀǰ�ڵ�ĸ���
	**/
	int reduce(void** playload);
	/**
	* @brief ��ȡ�����е�һ�����أ�������ɾ��
	* @param pos λ��
	* @param return ����ָ��
	**/
	void* get(unsigned int pos);
	/**
	* @brief ��ȡ������
	* @param return ������
	**/
	unsigned int linkSize() const;
	/**
	* @brief �ͷ�����
	**/
	void clear();
private:
	Node* find(unsigned int pos);
	void release();
	struct LinkManager m_manager;
};

}//Infra

#endif //__LINK_H__
