﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using FarseerPhysics.Dynamics;

namespace Brainstorm_Studios_Game_Engine
{
    class BSCamera
    {
        
        public Vector2 Position { get { return new Vector2(BSConverter.MeterToPixel(position.X) - Viewport.Width / 2, BSConverter.MeterToPixel(position.Y) - Viewport.Height / 2); } }
        public Vector2 position;
        Vector2 _minPosition;
        Vector2 _maxPosition;
        Vector2 _translateCenter;
        Vector2 _targetPosition;
        public Matrix Projection;
        public Matrix View;
        public Matrix DebugView;
        public Viewport Viewport { get; set; }
        public bool IsFollowing { get; set; }
        public float Scale { get; set; }
        Body ObjectToFollow;
        public void ResetCamera()
        {
            position = Vector2.Zero;
            _maxPosition = Vector2.Zero;
            _minPosition = Vector2.Zero;
            SetView();
        }

        public void SetView()
        {
            Vector3 translateCenter = new Vector3(_translateCenter, 0f);
            Vector3 translateBody = new Vector3(-position, 0f);

            DebugView = Matrix.CreateTranslation(translateBody) *Matrix.CreateScale(Scale)*
                    Matrix.CreateTranslation(translateCenter);

            translateBody = BSConverter.MeterToPixel(translateBody);
            translateCenter = BSConverter.MeterToPixel(translateCenter);

            View = Matrix.CreateTranslation(translateBody) *Matrix.CreateScale(Scale)*
                    Matrix.CreateTranslation(translateCenter);

        }
        public BSCamera(Viewport viewport)
        {
            IsFollowing = false;
            this.Viewport = viewport;
            position = Vector2.Zero;
            View = Matrix.Identity;
            DebugView = Matrix.Identity;
            Projection = Matrix.CreateOrthographicOffCenter(0,
                BSConverter.PixelToMeter(viewport.Width),
                BSConverter.PixelToMeter(viewport.Height),
                0, 0f, 1f);
            _translateCenter = new Vector2(
                    BSConverter.PixelToMeter(viewport.Width / 2f),
                    BSConverter.PixelToMeter(viewport.Height / 2f));
            Scale = 0.8f;

        }
        public void Follow(Body obj)
        {
            IsFollowing = true;
            ObjectToFollow=obj;
        }
        public void Update()
        {
            if (ObjectToFollow != null)
            {
                _targetPosition = ObjectToFollow.Position;
                position = ObjectToFollow.Position;
                if (_minPosition != _maxPosition)
                {
                    Vector2.Clamp(ref _targetPosition, ref _minPosition, ref _maxPosition, out _targetPosition);
                }
            }
            SetView();
        }
        public void Update(GameTime gameTime)
        {
            if (ObjectToFollow != null)
            {
                _targetPosition = ObjectToFollow.Position;
                position = ObjectToFollow.Position;
                if (_minPosition != _maxPosition)
                {
                    Vector2.Clamp(ref _targetPosition, ref _minPosition, ref _maxPosition, out _targetPosition);
                }
            }/*
            Vector2 delta = _targetPosition - Position;
            float distance = delta.Length();
            if (distance > 0f)
            {
                delta /= distance;
            }
            float inertia;
            if (distance < 10f)
            {
                inertia = (float)Math.Pow(distance / 10.0, 2.0);
            }
            else
            {
                inertia = 1f;
            }

            Position += 64f*inertia * delta  * (float)gameTime.ElapsedGameTime.TotalSeconds;
            */
            SetView();
        }
    }
}
