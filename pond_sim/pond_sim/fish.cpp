
#include "fish.h"

#include <algorithm>
#include <cstdint>
#include <random>

namespace {

	const float kPi = 3.14159265358979f;
	const sf::Color eyeColor(255, 255, 255);
	const sf::Color pupilColor(15, 15, 20);

	std::mt19937& rng() {
		static std::mt19937 generator{ std::random_device{}() };
		return generator;
	}

	float randomFloat(float low, float high) {
		return std::uniform_real_distribution<float>(low, high)(rng());
	}

	float mix(float a, float b, float t) {
		return a + (b - a) * t;
	}

	float smoothstep(float t) {
		t = std::clamp(t, 0.f, 1.f);
		return t * t * (3.f - 2.f * t);
	}

	float wrapAngle(float angle) {
		while (angle > kPi) angle -= 2.f * kPi;
		while (angle < -kPi) angle += 2.f * kPi;
		return angle;
	}

	float lengthOf(sf::Vector2f v) {
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	sf::Vector2f normalized(sf::Vector2f v) {
		float len = lengthOf(v);
		if (len < 1e-5f) {
			return { 1.f, 0.f };
		}
		return v / len;
	}

	sf::Vector2f tangentAt(const std::vector<sf::Vector2f>& points, int i) {
		int last = static_cast<int>(points.size()) - 1;
		return normalized(points[std::max(i - 1, 0)] - points[std::min(i + 1, last)]);
	}

	sf::Vector2f normalAt(const std::vector<sf::Vector2f>& points, int i) {
		sf::Vector2f t = tangentAt(points, i);
		return { -t.y, t.x };
	}

	sf::Color makeColor(const std::vector<int>& c, int alpha = 255) {
		if (c.size() < 3) {
			return sf::Color(255, 255, 255, static_cast<std::uint8_t>(alpha));
		}
		return sf::Color(
			static_cast<std::uint8_t>(std::clamp(c[0], 0, 255)),
			static_cast<std::uint8_t>(std::clamp(c[1], 0, 255)),
			static_cast<std::uint8_t>(std::clamp(c[2], 0, 255)),
			static_cast<std::uint8_t>(std::clamp(alpha, 0, 255)));
	}

	sf::Color colorFromHsv(float hue, float saturation, float value) {
		float chroma = value * saturation;
		float h = std::fmod(hue, 360.f) / 60.f;
		float second = chroma * (1.f - std::abs(std::fmod(h, 2.f) - 1.f));

		float r = 0.f, g = 0.f, b = 0.f;
		if (h < 1.f)      { r = chroma; g = second; }
		else if (h < 2.f) { r = second; g = chroma; }
		else if (h < 3.f) { g = chroma; b = second; }
		else if (h < 4.f) { g = second; b = chroma; }
		else if (h < 5.f) { r = second; b = chroma; }
		else              { r = chroma; b = second; }

		float m = value - chroma;
		return sf::Color(
			static_cast<std::uint8_t>((r + m) * 255.f + 0.5f),
			static_cast<std::uint8_t>((g + m) * 255.f + 0.5f),
			static_cast<std::uint8_t>((b + m) * 255.f + 0.5f));
	}

	float colorDistance(sf::Color a, sf::Color b) {
		float dr = float(a.r) - float(b.r);
		float dg = float(a.g) - float(b.g);
		float db = float(a.b) - float(b.b);
		return std::sqrt(dr * dr + dg * dg + db * db);
	}

}

Fish::Fish() {
	initBody();
};

Fish::Fish(int xCoordinate, int yCoordinate, std::string fishName, int fishSize, std::vector<int> fishColor) {
	x = static_cast<float>(xCoordinate);
	y = static_cast<float>(yCoordinate);
	name = fishName;
	size = fishSize;
	color = fishColor;
	color.resize(3, 255);

	direction = randomFloat(-kPi, kPi);
	cruiseSpeed = size * randomFloat(0.3f, 0.7f);
	maxTurnRate = randomFloat(1.4f, 2.0f);
	speed = cruiseSpeed;


	shape.body = randomFloat(1.f - partVariation, 1.f + partVariation);
	shape.tailBase = randomFloat(1.f - partVariation, 1.f + partVariation);
	shape.tailFlare = randomFloat(1.f - partVariation, 1.f + partVariation);
	shape.tailTip = randomFloat(1.f - partVariation, 1.f + partVariation);
	shape.bigFin = randomFloat(1.f - partVariation, 1.f + partVariation);
	shape.smallFin = randomFloat(1.f - partVariation, 1.f + partVariation);
	shape.eye = randomFloat(1.f - partVariation, 1.f + partVariation);


	int spotCount = 0;
	if (randomFloat(0.f, 1.f) >= noSpotChance) {
		spotCount = 3 + std::min(static_cast<int>(randomFloat(0.f, 3.f)), 2);  
	}
	for (int i = 0; i < spotCount; i++) {
		spots.push_back({ randomFloat(0.1f, 0.58f), randomFloat(-0.35f, 0.35f), randomFloat(0.4f, 0.6f), randomFloat(1.2f, 2.f) });
	}

	const sf::Color bodyColor = makeColor(color);
	for (int attempt = 0; attempt < 20; attempt++) {
		spotColor = colorFromHsv(randomFloat(0.f, 360.f), randomFloat(0.6f, 1.f), randomFloat(0.75f, 1.f));
		if (colorDistance(spotColor, bodyColor) > 120.f) {
			break;
		}
	}

	initBody();
};

void Fish::initBody() {
	float segmentLength = static_cast<float>(size) / (spineCount - 1);

	spine.assign(spineCount, sf::Vector2f(x, y));
	for (int i = 1; i < spineCount; i++) {
		spine[i] = { x - std::cos(direction) * segmentLength * i, y - std::sin(direction) * segmentLength * i };
	}
	bodyPoints = spine;
}

void Fish::pickTarget(const sf::FloatRect& bounds) {
	const float length = static_cast<float>(size);
	const float margin = length * wallMargin;
	const float minX = bounds.position.x + margin;
	const float maxX = bounds.position.x + bounds.size.x - margin;
	const float minY = bounds.position.y + margin;
	const float maxY = bounds.position.y + bounds.size.y - margin;

	hasTarget = true;
	retargetTimer = randomFloat(minWanderTime, maxWanderTime);

	if (maxX <= minX || maxY <= minY) {
		target = { bounds.position.x + bounds.size.x * 0.5f, bounds.position.y + bounds.size.y * 0.5f };
		return;
	}

	for (int attempt = 0; attempt < 10; attempt++) {
		float angle = direction + randomFloat(-0.5f, 0.5f);
		float dx = std::cos(angle);
		float dy = std::sin(angle);
		float distance = randomFloat(length * 2.f, length * 5.f);

		float room = distance;
		if (dx > 1e-4f) room = std::min(room, (maxX - x) / dx);
		else if (dx < -1e-4f) room = std::min(room, (minX - x) / dx);
		if (dy > 1e-4f) room = std::min(room, (maxY - y) / dy);
		else if (dy < -1e-4f) room = std::min(room, (minY - y) / dy);

		float travel = (room < distance) ? room * randomFloat(0.6f, 1.f) : distance;

		if (travel >= length) {
			target = { x + dx * travel, y + dy * travel };
			return;
		}
	}

	target = { randomFloat(minX, maxX), randomFloat(minY, maxY) };
}

float Fish::halfWidthAt(float t) const {
	const float length = static_cast<float>(size);
	const float widest = 0.25f;

	if (t < widest) {
		return length * maxBodyWidth * shape.body;
	}
	return length * mix(maxBodyWidth * shape.body, tailBaseWidth * shape.tailBase, smoothstep((t - widest) / (bodyEnd - widest)));
}

void Fish::update(float deltaTime, const sf::FloatRect& bounds) {

	if (size <= 0) {
		return;
	}

	deltaTime = std::min(deltaTime, 0.05f);

	const float length = static_cast<float>(size);

	retargetTimer -= deltaTime;
	sf::Vector2f toTarget = target - sf::Vector2f(x, y);
	if (!hasTarget || retargetTimer <= 0.f || lengthOf(toTarget) < length * 0.5f) {
		pickTarget(bounds);
		toTarget = target - sf::Vector2f(x, y);
	}

	float desired = std::atan2(toTarget.y, toTarget.x);
	float difference = wrapAngle(desired - direction);
	float maxTurn = maxTurnRate * deltaTime;
	direction = wrapAngle(direction + std::clamp(difference, -maxTurn, maxTurn));

	float turnAmount = std::min(std::abs(difference) / kPi, 1.f);
	float targetSpeed = cruiseSpeed * (1.f - 0.6f * turnAmount);
	speed += (targetSpeed - speed) * std::min(deltaTime * 2.f, 1.f);

	x += std::cos(direction) * speed * deltaTime;
	y += std::sin(direction) * speed * deltaTime;

	const float segmentLength = length / (spineCount - 1);
	spine[0] = { x, y };
	for (int i = 1; i < spineCount; i++) {
		sf::Vector2f away = spine[i] - spine[i - 1];
		spine[i] = spine[i - 1] + normalized(away) * segmentLength;
	}

	float speedRatio = cruiseSpeed > 0.f ? std::min(speed / cruiseSpeed, 1.f) : 0.f;
	wigglePhase += deltaTime * (3.f + speed * 0.12f);
	if (wigglePhase > 4.f * kPi) {
		wigglePhase -= 4.f * kPi;
	}

	float amplitude = length * wiggleAmount * (0.4f + 0.6f * speedRatio);
	for (int i = 0; i < spineCount; i++) {
		float t = static_cast<float>(i) / (spineCount - 1);
		float envelope = 0.15f + 0.85f * t * t;
		float offset = amplitude * envelope * std::sin(wigglePhase - i * 0.45f);
		bodyPoints[i] = spine[i] + normalAt(spine, i) * offset;
	}

	const float pad = length * 0.12f;
	const float left = bounds.position.x + pad;
	const float right = bounds.position.x + bounds.size.x - pad;
	const float top = bounds.position.y + pad;
	const float bottom = bounds.position.y + bounds.size.y - pad;

	float lowX = bodyPoints[0].x, highX = lowX;
	float lowY = bodyPoints[0].y, highY = lowY;
	for (const sf::Vector2f& p : bodyPoints) {
		lowX = std::min(lowX, p.x);
		highX = std::max(highX, p.x);
		lowY = std::min(lowY, p.y);
		highY = std::max(highY, p.y);
	}

	sf::Vector2f shift(0.f, 0.f);
	if (highX - lowX <= right - left) {
		if (lowX < left) shift.x = left - lowX;
		else if (highX > right) shift.x = right - highX;
	}
	if (highY - lowY <= bottom - top) {
		if (lowY < top) shift.y = top - lowY;
		else if (highY > bottom) shift.y = bottom - highY;
	}

	if (shift.x != 0.f || shift.y != 0.f) {
		x += shift.x;
		y += shift.y;
		for (sf::Vector2f& p : spine) p += shift;
		for (sf::Vector2f& p : bodyPoints) p += shift;
	}
}

void Fish::draw(float /*deltaTime*/, sf::RenderWindow& surface) {

	if (size <= 0 || static_cast<int>(bodyPoints.size()) != spineCount) {
		return;
	}

	const float length = static_cast<float>(size);
	const int last = spineCount - 1;
	const int bodyLast = static_cast<int>(bodyEnd * last + 0.5f);
	const float segmentLength = length / last;

	const sf::Color bodyColor = makeColor(color);
	const sf::Color finColor = makeColor(color, 170);

	{
		auto tailWidth = [&](int i) {
			float u = static_cast<float>(i - bodyLast) / static_cast<float>(last - 1 - bodyLast);
			return mix(halfWidthAt(1.f), length * tailFlareWidth * shape.tailFlare, smoothstep(u));
		};
		auto tailColor = [&](int i) {
			float u = static_cast<float>(i - bodyLast) / static_cast<float>(last - bodyLast);
			return makeColor(color, static_cast<int>(mix(170.f, 80.f, u)));
		};

		sf::VertexArray tail(sf::PrimitiveType::Triangles);

		for (int i = bodyLast; i < last - 1; i++) {
			sf::Vector2f n0 = normalAt(bodyPoints, i);
			sf::Vector2f n1 = normalAt(bodyPoints, i + 1);
			float w0 = tailWidth(i);
			float w1 = tailWidth(i + 1);

			sf::Vertex left0{ bodyPoints[i] + n0 * w0, tailColor(i) };
			sf::Vertex right0{ bodyPoints[i] - n0 * w0, tailColor(i) };
			sf::Vertex left1{ bodyPoints[i + 1] + n1 * w1, tailColor(i + 1) };
			sf::Vertex right1{ bodyPoints[i + 1] - n1 * w1, tailColor(i + 1) };

			tail.append(left0);
			tail.append(right0);
			tail.append(left1);

			tail.append(right0);
			tail.append(right1);
			tail.append(left1);
		}

		sf::Vector2f nBase = normalAt(bodyPoints, last - 1);
		float baseWidth = tailWidth(last - 1);
		sf::Vector2f nTip = normalAt(bodyPoints, last);
		sf::Vector2f tTip = tangentAt(bodyPoints, last);
		float tipWidth = length * tailTipWidth * shape.tailTip;

		sf::Vertex middle{ bodyPoints[last - 1], tailColor(last - 1) };
		sf::Vertex baseLeft{ bodyPoints[last - 1] + nBase * baseWidth, tailColor(last - 1) };
		sf::Vertex baseRight{ bodyPoints[last - 1] - nBase * baseWidth, tailColor(last - 1) };
		sf::Vertex tipLeft{ bodyPoints[last] + nTip * tipWidth, tailColor(last) };
		sf::Vertex tipRight{ bodyPoints[last] - nTip * tipWidth, tailColor(last) };
		sf::Vertex notch{ bodyPoints[last] + tTip * (segmentLength * 0.8f), tailColor(last) };

		tail.append(middle);   tail.append(baseLeft);  tail.append(tipLeft);
		tail.append(middle);   tail.append(tipLeft);   tail.append(notch);
		tail.append(middle);   tail.append(notch);     tail.append(tipRight);
		tail.append(middle);   tail.append(tipRight);  tail.append(baseRight);

		surface.draw(tail);
	}

	auto drawFin = [&](int index, float side, float finLength, float sweep) {
		sf::Vector2f n = normalAt(bodyPoints, index);
		sf::Vector2f t = tangentAt(bodyPoints, index);
		float halfWidth = halfWidthAt(static_cast<float>(index) / last);

		sf::Vector2f anchor = bodyPoints[index] + n * (side * halfWidth * 0.85f);
		float angle = std::atan2(t.y, t.x) + kPi - side * sweep;

		sf::CircleShape fin(finLength * 0.5f, 24);
		fin.setOrigin({ 0.f, finLength * 0.5f });
		fin.setScale({ 1.f, 0.4f });
		fin.setPosition(anchor);
		fin.setRotation(sf::radians(angle));
		fin.setFillColor(finColor);
		surface.draw(fin);
	};

	float flap = std::sin(wigglePhase * 0.5f);
	for (float side : { 1.f, -1.f }) {
		drawFin(3, side, length * bigFinSize * shape.bigFin, 0.75f + 0.2f * flap);
		drawFin(8, side, length * smallFinSize * shape.smallFin, 0.65f - 0.15f * flap);
	}

	{
		sf::VertexArray body(sf::PrimitiveType::TriangleStrip);

		for (int i = 0; i <= bodyLast; i++) {
			float halfWidth = halfWidthAt(static_cast<float>(i) / last);
			sf::Vector2f n = normalAt(bodyPoints, i);

			body.append(sf::Vertex{ bodyPoints[i] + n * halfWidth, bodyColor });
			body.append(sf::Vertex{ bodyPoints[i] - n * halfWidth, bodyColor });
		}
		surface.draw(body);

		float noseRadius = halfWidthAt(0.f);
		sf::CircleShape nose(noseRadius, 24);
		nose.setOrigin({ noseRadius, noseRadius });
		nose.setPosition(bodyPoints[0]);
		nose.setFillColor(bodyColor);
		surface.draw(nose);
	}

	for (const Spot& spot : spots) {
		float position = spot.t * last;
		int i = std::min(static_cast<int>(position), last - 1);
		float fraction = position - i;

		sf::Vector2f along(mix(bodyPoints[i].x, bodyPoints[i + 1].x, fraction),
						   mix(bodyPoints[i].y, bodyPoints[i + 1].y, fraction));
		sf::Vector2f n = normalAt(bodyPoints, i);
		sf::Vector2f t = tangentAt(bodyPoints, i);
		float halfWidth = halfWidthAt(spot.t);
		float radius = spot.radius * halfWidth;

		sf::CircleShape patch(radius, 20);
		patch.setOrigin({ radius, radius });
		patch.setScale({ spot.stretch, 1.f });
		patch.setPosition(along + n * (spot.lateral * halfWidth));
		patch.setRotation(sf::radians(std::atan2(t.y, t.x)));
		patch.setFillColor(spotColor);
		surface.draw(patch);
	}

	{
		sf::Vector2f n = normalAt(bodyPoints, 1);
		float eyeRadius = eyeSize * shape.eye;
		float pupilRadius = eyeRadius * pupilSize;
		float eyeOffset = std::max(halfWidthAt(1.f / last) * 0.7f, eyeRadius);

		for (float side : { 1.f, -1.f }) {
			sf::Vector2f eyePosition = bodyPoints[1] + n * (side * eyeOffset);

			sf::CircleShape eye(eyeRadius, 16);
			eye.setOrigin({ eyeRadius, eyeRadius });
			eye.setPosition(eyePosition);
			eye.setFillColor(eyeColor);
			surface.draw(eye);

			sf::CircleShape pupil(pupilRadius, 12);
			pupil.setOrigin({ pupilRadius, pupilRadius });
			pupil.setPosition(eyePosition);
			pupil.setFillColor(pupilColor);
			surface.draw(pupil);
		}
	}
}


float Fish::getX() const {
	return x;
}

float Fish::getY() const {
	return y;
}

float Fish::getDirection() const {
	return direction;
}

float Fish::getSpeed() const {
	return speed;
}

int Fish::getSize() const {
	return size;
}

std::vector<int> Fish::getColor() const {
	return color;
}

std::string Fish::getName() const {
	return name;
}
