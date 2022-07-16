function world2d.OnMousePressed(x, y, button)
	print("OnMousePressed", x, y, button)
end

function world2d.OnMouseReleased(x, y, button)
	print("OnMouseReleased", x, y, button)
end

function world2d.OnMouseMotion(x, y, xrel, yrel)
	print("OnMouseMotion", x, y, xrel, yrel)
end

function world2d.OnMouseWheelMotion(x, y, direction, preciseX, preciseY)
	print("OnMouseWheelMotion", x, y, direction, preciseX, preciseY)
end