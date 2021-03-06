#pragma once
#include "complex.hpp"


Complex::Complex()
	: Complex(0, 0) {}

Complex::Complex(double rp)
	: Complex(rp, 0) {}

Complex::Complex(double rp, double ip)
	: r(rp), i(ip) {}

Complex Complex::operator+(const Complex& c) const
{
	return Complex(r + c.r, i + c.i);
}

Complex Complex::operator+(const double rat) const
{
	return Complex(r + rat, i);
}

Complex& Complex::operator+=(const Complex& c)
{
	r += c.r;
	i += c.i;

	return *this;
}

Complex& Complex::operator+=(const double rat)
{
	r += rat;

	return *this;
}

Complex Complex::operator-(const Complex& c) const
{
	return Complex(r - c.r, i - c.i);
}

Complex Complex::operator-(const double rat) const
{
	return Complex(r - rat, i);
}

Complex& Complex::operator-=(const Complex& c)
{
	r -= c.r;
	i -= c.i;

	return *this;
}

Complex& Complex::operator-=(const double rat)
{
	r -= rat;

	return *this;
}

Complex Complex::operator*(const Complex& c) const
{
	double* pair = this->mult(c);

	Complex res(pair[0], pair[1]);

	delete[] pair;

	return res;
}

Complex Complex::operator*(const double rat) const
{
	double* pair = this->mult(Complex(rat));

	Complex res(pair[0], pair[1]);

	delete[] pair;

	return res;
}

Complex& Complex::operator*=(const Complex& c)
{
	double* pair = this->mult(c);

	r = pair[0];
	i = pair[1];

	delete[] pair;

	return *this;
}

Complex& Complex::operator*=(const double rat)
{
	double* pair = this->mult(Complex(rat));

	r = pair[0];
	i = pair[1];

	delete[] pair;

	return *this;
}

Complex Complex::operator/(const Complex& c) const
{
	double* pair = this->div(c);

	Complex res(pair[0], pair[1]);

	delete[] pair;

	return res;
}

Complex Complex::operator/(const double rat) const
{
	double* pair = this->div(Complex(rat));

	Complex res(pair[0], pair[1]);

	delete[] pair;

	return res;
}

Complex& Complex::operator/=(const Complex& c)
{
	double* pair = this->div(c);

	r = pair[0];
	i = pair[1];

	delete[] pair;

	return *this;
}

Complex& Complex::operator/=(const double rat)
{
	double* pair = this->div(Complex(rat));

	r = pair[0];
	i = pair[1];

	delete[] pair;

	return *this;
}

Complex Complex::operator-() const
{
	return Complex(-r, -i);
}

bool Complex::operator==(const Complex& c) const
{
	return equals(r, c.r) && equals(i, c.i);
}

bool Complex::operator!=(const Complex& c) const
{
	return !equals(r, c.r) || !equals(i, c.i);
}

std::ostream& operator<<(std::ostream& out, const Complex& complex)
{
	out << complex.toString();

	return out;
}

double Complex::getRationalPart() const
{
	return r;
}

double Complex::getImaginePart() const
{
	return i;
}

Complex Complex::getComplement() const
{
	return Complex(r, -i);
}

double Complex::to_rational() const
{
	return sqrt(r * r + i * i);
}

std::string Complex::toString() const
{
	std::stringstream ss;

	if (r == 0)
	{
		if (i == 0)
		{
			ss << 0;
		}
		else
		{
			ss << i << 'i';
		}
	}
	else
	{
		ss << r;

		if (i != 0)
		{
			if (i < 0)
			{
				ss << " - " << -i;
			}
			else
			{
				ss << " + " << i;
			}

			ss << 'i';
		}
	}

	return ss.str();
}

int Complex::length() const
{
	return toString().length();
}

double* Complex::mult(const Complex& c) const
{
	double* res = new double[2];
	double
		a1 = r,
		a2 = c.r,
		b1 = i,
		b2 = c.i;

	res[0] = a1 * a2 - b1 * b2;
	res[1] = a1 * b2 + b1 * a2;

	return res;
}

double* Complex::div(const Complex& c) const
{
	double* res = new double[2];
	double
		a1 = r,
		a2 = c.r,
		b1 = i,
		b2 = c.i;
	double d = (a2 * a2 + b2 * b2);

	res[0] = (a1 * a2 + b1 * b2) / d;
	res[1] = (b1 * a2 - a1 * b2) / d;

	return res;
}

bool Complex::equals(double a, double b) const
{
	const double eps = 0.000001;
	return fabs(a - b) <= eps;
}