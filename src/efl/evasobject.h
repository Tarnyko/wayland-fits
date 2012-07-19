#ifndef __WAYLAND_EFL_EVAS_OBJECT_H__
#define __WAYLAND_EFL_EVAS_OBJECT_H__

class EvasObject
{
public:
	EvasObject(Evas_Object* = NULL);

	virtual ~EvasObject();

	void setSize(int w, int h);
	void setPosition(int x, int y);
	void show();

	const int getWidth();
	const int getHeight();
	const int getX();
	const int getY();
	const Eina_Bool isVisible();

	operator Evas*();
	operator Ecore_Evas*();
	operator Evas_Object*();

	void checkSize(const int width, const int height);
	void checkPosition(const int x, const int y);
	void checkVisible(const Eina_Bool isVisible);

private:
	Evas_Object*	obj_;

};

#define SET_CHECK_SIZE(obj, w, h)\
		queueCallback( \
			ModifyCheckCallback( \
				boost::bind(&EvasObject::setSize, boost::ref(obj), w, h), \
				boost::bind(&EvasObject::checkSize, boost::ref(obj), w, h) \
			) \
		)

#define SET_CHECK_POSITION(obj, x, y) \
		queueCallback( \
			ModifyCheckCallback( \
				boost::bind(&EvasObject::setPosition, boost::ref(obj), x, y), \
				boost::bind(&EvasObject::checkPosition, boost::ref(obj), x, y) \
			) \
		)

#define SET_CHECK_SHOW(obj) \
		queueCallback( \
			ModifyCheckCallback( \
				boost::bind(&EvasObject::show, boost::ref(obj)), \
				boost::bind(&EvasObject::checkVisible, boost::ref(obj), EINA_TRUE) \
			) \
		)

#endif
