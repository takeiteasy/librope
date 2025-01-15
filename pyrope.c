#include <Python.h>
#define ROPE_WCHAR 1
#include "rope.h"

typedef struct {
    PyObject_HEAD
    rope *ptr;
} PyRope;

static PyObject* PyRope_New(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    PyRope* self = (PyRope*)type->tp_alloc(type, 0);
    if (!self || !(self->ptr = rope_new()))
        return NULL;
    const char *str = NULL;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        Py_DECREF(self);
        return NULL;
    }
    return (PyObject*)self;
}

static void PyRope_Dealloc(PyRope* self) {
    if (self->ptr)
        rope_free(self->ptr);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyMethodDef PyRope_methods[] = {
    {NULL, NULL, 0, NULL}
};

static PyTypeObject PyRopeType = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "pyrope.PyRope",                            /* tp_name */
    sizeof(PyRope),                             /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)PyRope_Dealloc,                 /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    0,                                          /* tp_repr */
    0,                                          /* tp_as_number */
    0,                                          /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    0,                                          /* tp_hash */
    0,                                          /* tp_call */
    0,                                          /* tp_str */
    0,                                          /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                         /* tp_flags */
    PyDoc_STR("PyRope object"),                 /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    PyRope_methods,                             /* tp_methods */
    0,                                          /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    0,                                          /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)PyRope_New,                        /* tp_new */
};

static PyMethodDef pyrope_methods[] = {
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyrope_module = {
    PyModuleDef_HEAD_INIT,
    "pyrope",
    "Python bindings for librope",
    -1,
    pyrope_methods
};

PyMODINIT_FUNC PyInit_pyrope(void) {
    if (PyType_Ready(&PyRopeType) < 0)
        return NULL;
    PyObject *m = PyModule_Create(&pyrope_module);
    if (!m)
        return NULL;
    Py_INCREF(&PyRopeType);
    if (PyModule_AddObject(m, "PyRope", (PyObject*)&PyRopeType) < 0) {
        Py_DECREF(&PyRopeType);
        Py_DECREF(m);
        return NULL;
    }
    return m;
}
